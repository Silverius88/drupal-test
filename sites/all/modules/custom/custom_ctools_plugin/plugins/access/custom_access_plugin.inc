<?php

/**
 * @file
 *
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Registered years ago'),
  'description' => t('Controls access depends on registered years ago'),
  'callback' => 'custom_access_plugin_registered_years_ago_access',
  'default' => array('registered_years_ago' => 0),
  'settings form' => 'custom_access_plugin_registered_years_ago_access_settings_form',
  'summary' => 'custom_access_plugin_registered_years_ago_access_summary',
  'required context' => new ctools_context_required(t('User'), 'user'),
);

/**
 * Settings form for plugin.
 */
function custom_access_plugin_registered_years_ago_access_settings_form(&$form, &$form_state, $conf) {
  $options = _custom_access_plugin_years_ago_get_values();
  $form = array();
  $form['settings']['registered_years_ago'] = array(
    '#type' => 'select',
    '#title' => t('Select how many year ago registered current user'),
    '#options' => $options,
    '#default_value' => !empty($conf['registered_years_ago']) ? $conf['registered_years_ago'] : 0,
    '#description' => t('Only users with the selected permission flag will be able to access this.'),
  );
  return $form;
}

/**
 * Array options custom_access_plugin_registered_years_ago_access_settings_form
 * @return array
 */
function _custom_access_plugin_years_ago_get_values() {
  return array(
    0 => t('less then 1 years'),
    1 => t('from 1 to 2 years ago'),
    2 => t('from 2 to 3 years ago'),
    3 => t('3 and more years ago'),
  );
}

/**
 * Provide a summary description based on selected settings.
 */
function custom_access_plugin_registered_years_ago_access_summary($conf, $context) {
  $options = _custom_access_plugin_years_ago_get_values();
  return t('User registered ' . $options[$conf['registered_years_ago']]);
}

/**
 * Check for access.
 */
function custom_access_plugin_registered_years_ago_access($conf, $context) {
  global $user;
  // As far as I know there should always be a context at this point, but this
  // is safe.
  if (empty($context) || empty($context->data)) {
    return FALSE;
  }

  if ($user->uid == 0) {
    return FALSE;
  }

  switch ($conf['registered_years_ago']) {
    case 0:
      $time_start = strtotime("-1 year", time());
      $return = ($user->created > $time_start) ? TRUE : FALSE;
      break;
    case 1:
      $time_start = strtotime("-2 year", time());
      $time_end = strtotime("-1 year", time());
      $return = ($user->created > $time_start && $user->created <= $time_end) ? TRUE : FALSE;
      break;
    case 2:
      $time_start = strtotime("-3 year", time());
      $time_end = strtotime("-2 year", time());
      $return = ($user->created > $time_start && $user->created <= $time_end) ? TRUE : FALSE;
      break;
    case 3:
      $time_start = strtotime("-3 year", time());
      $return = ($user->created <= $time_start) ? TRUE : FALSE;
      break;
    default:
      $return = FALSE;
  }

  return $return;
}