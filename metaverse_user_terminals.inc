<?php

/**
 * @package    metaverse_user
 * @copyright Copyright (C) 2013 Wene - ssm2017 Binder ( S.Massiaux ). All rights reserved.
 * @license   GNU/GPL, http://www.gnu.org/licenses/gpl-2.0.html
 * metaverse_user is free software. This version may have been modified pursuant
 * to the GNU General Public License, and as distributed it includes or
 * is derivative of works licensed under the GNU General Public License or
 * other free or open source software licenses.
 */

function metaverse_user_manage_terminal($values) {
	// check if the terminal exists
	$terminals = metaverse_user_get_terminals_by_key(array('terminal_key' => $values->objectkey));

	if (is_null($terminals)) {
		drupal_set_message(t('no terminals found by id'));
		// check if there is already a terminal on this region
		$terminals = metaverse_user_get_terminals_by_region(array('owner_key' => $values->ownerkey, 'region_name' => $values->region_name));
		if (!is_null($terminals)) {
			drupal_set_message(t('!qty terminals found by region', array('!qty' => count($terminals))));
			// delete terminals
			metaverse_user_delete_terminals($terminals);
			$terminals = NULL;
			drupal_set_message(t('terminals deleted'));
		}
	}
	else {
		if (count($terminals) > 1) {
			// delete terminals
			metaverse_user_delete_terminals($terminals);
			$terminals = NULL;
			drupal_set_message(t('terminals deleted'));
		}
		else {
			// update terminal
			$values->nid = $terminals[0];
			$terminal = metaverse_user_save_terminal($values, FALSE);
			drupal_set_message(t('terminal updated'));
		}
	}
	if (is_null($terminals)) {
		// create a new terminal
		$terminal = metaverse_user_save_terminal($values);
		drupal_set_message(t('terminal created'));
	}
	return $terminal;
}

function metaverse_user_get_terminals_by_key($values) {
	$query = new EntityFieldQuery();
	$entities = $query->entityCondition('entity_type', 'node')
			->propertyCondition('type', 'metaverse_user_terminal')
			->fieldCondition('field_mu_terminal_key', 'value', $values['terminal_key'])
			->execute();
	if (isset($entities['node'])) {
		$nodes_ids = array();
		foreach ($entities['node'] as $n) {
			$nodes_ids[] = $n->nid;
		}
		// get the nodes
		return $nodes_ids;
	}
	return NULL;
}

function metaverse_user_get_terminals_by_region($values) {
	$query = new EntityFieldQuery();
	$entities = $query->entityCondition('entity_type', 'node')
			->propertyCondition('type', 'metaverse_user_terminal')
			->fieldCondition('field_mu_terminal_owner_key', 'value', $values['owner_key'])
			->fieldCondition('field_mu_region_name', 'value', $values['region_name'])
			->execute();
	if (isset($entities['node'])) {
		$nodes_ids = array();
		foreach ($entities['node'] as $n) {
			$nodes_ids[] = $n->nid;
		}
		return $nodes_ids;
	}
	return NULL;
}

function metaverse_user_save_terminal($values, $args = array(), $is_new = TRUE) {
	if ($is_new) {
		$node = new stdClass();
		$node->type = 'metaverse_user_terminal';
		node_object_prepare($node);
	}
	else {
		$node = node_load($values->nid);
	}

	$node->uid = 1;

	if (module_exists('d4os_ui_users')) {
		// get the uid of the terminal owner
		$uid = db_query("SELECT uid FROM {d4os_ui_users} WHERE UUID = :uuid", array(':uuid' => $values->ownerkey))->fetchField();
		if ($uid !== FALSE && !is_null($uid)) {
			$node->uid = $uid;
		}
	}
	$node->title = $values->objectname;
	$node->language = LANGUAGE_NONE;

	$node->body[$node->language][0]['value'] = '';
	$node->body[$node->language][0]['summary'] = text_summary('');
	$node->body[$node->language][0]['format'] = 'plain_text';

	$node->field_mu_terminal_key[$node->language][0]['value'] = $values->objectkey;
	if (isset($args['terminal_url'])) {
		$node->field_mu_terminal_url[$node->language][0]['value'] = base64_decode($args['terminal_url']);
	}
	$node->field_mu_terminal_owner_key[$node->language][0]['value'] = $values->ownerkey;
	$node->field_mu_region_name[$node->language][0]['value'] = $values->region_name;
	$node->field_mu_terminal_location[$node->language][0]['value'] = '<'.floor($values->position_x).','.floor($values->position_y).','.floor($values->position_z).'>';

	node_save($node);
	return $node;
}

function metaverse_user_delete_terminals($terminals_nids) {
	foreach ($terminals_nids as $terminal_nid) {
		// delete parcels
		$parcels_nids = metaverse_user_get_parcels_by_terminal_nid(array('terminal_nid' => $terminal_nid));
		if (!is_null($parcels_nids)) {
			node_delete_multiple($parcels_nids);
		}
	}
	// delete terminals
	node_delete_multiple($terminals_nids);
}

/**********************
 *			INWORLD
 **********************/
function metaverse_user_inworld_save_terminal (&$sl, $args) {
	// check if the terminal url is answering
	if (isset($args['terminal_url'])) {
		$response = metaverse_framework_http_request(base64_decode($args['terminal_url']). 'ping');
		if ($response->code != 200 || $response->data != 'pong') {
			drupal_set_message(t('Terminal is not answering : !error ', array('!error' => $response->message)));
			$sl->response['status'] = FALSE;
			$sl->response['message'] = "error;". metaverse_framework_get_messages();
			return;
		}
	}
	else {
		drupal_set_message(t('No url given.'));
		$sl->response['status'] = FALSE;
		$sl->response['message'] = "error;". metaverse_framework_get_messages();
		return;
	}
	// check if the terminal exists
	$terminals = metaverse_user_get_terminals_by_key(array('terminal_key' => $sl->objectkey));

	if (is_null($terminals)) {
		drupal_set_message(t('no terminals found by id'));
		// check if there is already a terminal on this region
		$terminals = metaverse_user_get_terminals_by_region(array('owner_key' => $sl->ownerkey, 'region_name' => $sl->region_name));
		if (!is_null($terminals)) {
			drupal_set_message(t('!qty terminals found by region', array('!qty' => count($terminals))));
			// delete terminals
			metaverse_user_delete_terminals($terminals);
			$terminals = NULL;
			drupal_set_message(t('terminals deleted'));
		}
	}
	else {
		if (count($terminals) > 1) {
			// delete terminals
			metaverse_user_delete_terminals($terminals);
			$terminals = NULL;
			drupal_set_message(t('terminals deleted'));
		}
		else {
			// update terminal
			$sl->nid = $terminals[0];
			$terminal = metaverse_user_save_terminal($sl, $args, FALSE);
			drupal_set_message(t('terminal updated'));
		}
	}
	if (is_null($terminals)) {
		// create a new terminal
		$terminal = metaverse_user_save_terminal($sl, $args);
		drupal_set_message(t('terminal created'));
	}
	if (is_object($terminal)) {
		$sl->response['status'] = TRUE;
		$sl->response['message'] = "success;". metaverse_framework_get_messages();
	}
	else {
		$sl->response['status'] = FALSE;
		$sl->response['message'] = "error;". metaverse_framework_get_messages();
	}
}
