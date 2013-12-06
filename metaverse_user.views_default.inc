<?php

/**
 * @package   metaverse_user
 * @copyright Copyright (C) 2013 Wene - ssm2017 Binder ( S.Massiaux ). All rights reserved.
 * @link      http://www.d4os.org
 * @license   GNU/GPL, http://www.gnu.org/licenses/gpl-2.0.html
 * metaverse_user is free software. This version may have been modified pursuant
 * to the GNU General Public License, and as distributed it includes or
 * is derivative of works licensed under the GNU General Public License or
 * other free or open source software licenses.
 */

/**
 * Implements hook_views_default_views.
 */
function metaverse_user_views_default_views() {
	return array(
		'metaverse_terminals' => metaverse_user_terminals_views()
	);
}

function metaverse_user_terminals_views() {
	$view = new view();
	$view->name = 'metaverse_terminals';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = 'Metaverse Terminals';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Metaverse Terminals';
	$handler->display->display_options['use_ajax'] = TRUE;
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'full';
	$handler->display->display_options['pager']['options']['items_per_page'] = '10';
	$handler->display->display_options['style_plugin'] = 'table';
	$handler->display->display_options['style_options']['grouping'] = array(
		0 => array(
			'field' => 'name',
			'rendered' => 1,
			'rendered_strip' => 0,
		),
	);
	$handler->display->display_options['style_options']['columns'] = array(
		'title' => 'title',
		'name' => 'name',
		'edit_node' => 'edit_node',
		'delete_node' => 'delete_node',
	);
	$handler->display->display_options['style_options']['default'] = '-1';
	$handler->display->display_options['style_options']['info'] = array(
		'title' => array(
			'sortable' => 0,
			'default_sort_order' => 'asc',
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
		'name' => array(
			'sortable' => 0,
			'default_sort_order' => 'asc',
			'align' => '',
			'separator' => '',
			'empty_column' => 0,
		),
		'edit_node' => array(
			'align' => '',
			'separator' => '',
			'empty_column' => 1,
		),
		'delete_node' => array(
			'align' => '',
			'separator' => '',
			'empty_column' => 1,
		),
	);
	/* No results behavior: Global: Text area */
	$handler->display->display_options['empty']['area']['id'] = 'area';
	$handler->display->display_options['empty']['area']['table'] = 'views';
	$handler->display->display_options['empty']['area']['field'] = 'area';
	$handler->display->display_options['empty']['area']['empty'] = TRUE;
	$handler->display->display_options['empty']['area']['content'] = 'No terminal found';
	$handler->display->display_options['empty']['area']['format'] = 'plain_text';
	/* Relationship: Content: Author */
	$handler->display->display_options['relationships']['uid']['id'] = 'uid';
	$handler->display->display_options['relationships']['uid']['table'] = 'node';
	$handler->display->display_options['relationships']['uid']['field'] = 'uid';
	/* Field: Content: Region name */
	$handler->display->display_options['fields']['field_mu_region_name']['id'] = 'field_mu_region_name';
	$handler->display->display_options['fields']['field_mu_region_name']['table'] = 'field_data_field_mu_region_name';
	$handler->display->display_options['fields']['field_mu_region_name']['field'] = 'field_mu_region_name';
	$handler->display->display_options['fields']['field_mu_region_name']['label'] = 'Region';
	/* Field: User: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'users';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['relationship'] = 'uid';
	$handler->display->display_options['fields']['name']['label'] = 'Owner';
	$handler->display->display_options['fields']['name']['exclude'] = TRUE;
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['label'] = 'Name';
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
	/* Field: Content: Last online */
	$handler->display->display_options['fields']['field_mu_terminal_last_online']['id'] = 'field_mu_terminal_last_online';
	$handler->display->display_options['fields']['field_mu_terminal_last_online']['table'] = 'field_data_field_mu_terminal_last_online';
	$handler->display->display_options['fields']['field_mu_terminal_last_online']['field'] = 'field_mu_terminal_last_online';
	$handler->display->display_options['fields']['field_mu_terminal_last_online']['settings'] = array(
		'format_type' => 'short',
		'fromto' => 'both',
		'multiple_number' => '',
		'multiple_from' => '',
		'multiple_to' => '',
	);
	/* Field: Content: Edit link */
	$handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
	$handler->display->display_options['fields']['edit_node']['label'] = '';
	$handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['edit_node']['hide_empty'] = TRUE;
	/* Field: Content: Delete link */
	$handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
	$handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
	$handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
	$handler->display->display_options['fields']['delete_node']['label'] = '';
	$handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
	$handler->display->display_options['fields']['delete_node']['hide_empty'] = TRUE;
	/* Sort criterion: Content: Last online (field_mu_terminal_last_online) */
	$handler->display->display_options['sorts']['field_mu_terminal_last_online_value']['id'] = 'field_mu_terminal_last_online_value';
	$handler->display->display_options['sorts']['field_mu_terminal_last_online_value']['table'] = 'field_data_field_mu_terminal_last_online';
	$handler->display->display_options['sorts']['field_mu_terminal_last_online_value']['field'] = 'field_mu_terminal_last_online_value';
	$handler->display->display_options['sorts']['field_mu_terminal_last_online_value']['order'] = 'DESC';
	/* Filter criterion: Content: Published */
	$handler->display->display_options['filters']['status']['id'] = 'status';
	$handler->display->display_options['filters']['status']['table'] = 'node';
	$handler->display->display_options['filters']['status']['field'] = 'status';
	$handler->display->display_options['filters']['status']['value'] = 1;
	$handler->display->display_options['filters']['status']['group'] = 1;
	$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
	/* Filter criterion: Content: Type */
	$handler->display->display_options['filters']['type']['id'] = 'type';
	$handler->display->display_options['filters']['type']['table'] = 'node';
	$handler->display->display_options['filters']['type']['field'] = 'type';
	$handler->display->display_options['filters']['type']['value'] = array(
		'metaverse_user_terminal' => 'metaverse_user_terminal',
	);
	/* Filter criterion: Content: Region name (field_mu_region_name) */
	$handler->display->display_options['filters']['field_mu_region_name_value']['id'] = 'field_mu_region_name_value';
	$handler->display->display_options['filters']['field_mu_region_name_value']['table'] = 'field_data_field_mu_region_name';
	$handler->display->display_options['filters']['field_mu_region_name_value']['field'] = 'field_mu_region_name_value';
	$handler->display->display_options['filters']['field_mu_region_name_value']['exposed'] = TRUE;
	$handler->display->display_options['filters']['field_mu_region_name_value']['expose']['operator_id'] = 'field_mu_region_name_value_op';
	$handler->display->display_options['filters']['field_mu_region_name_value']['expose']['label'] = 'Region';
	$handler->display->display_options['filters']['field_mu_region_name_value']['expose']['operator'] = 'field_mu_region_name_value_op';
	$handler->display->display_options['filters']['field_mu_region_name_value']['expose']['identifier'] = 'field_mu_region_name_value';
	$handler->display->display_options['filters']['field_mu_region_name_value']['expose']['remember_roles'] = array(
		2 => '2',
		1 => 0,
	);

	/* Display: Page */
	$handler = $view->new_display('page', 'Page', 'page');
	$handler->display->display_options['path'] = 'metaverse-user/terminals';
	$handler->display->display_options['menu']['type'] = 'normal';
	$handler->display->display_options['menu']['title'] = 'Metaverse Terminals';
	return $view;
}