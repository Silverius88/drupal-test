<?php

/**
 * @file
 *
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Custom argument to context"),
  'keyword' => 'custom_argument',
  'description' => t('Creates a "custom_context" from the arg special from AAA.'),
  'context' => 'custom_argument_context',
  // 'settings form' => 'custom_argument_settings_form',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('custom context argument'),
  ),
);

/**
 * Get the custom_context_argument context using the arg.
 */
function custom_argument_context($arg = NULL, $conf = NULL, $empty = FALSE) {
  // If $empty == TRUE it wants a generic, unfilled context.
  if ($empty) {
    return ctools_context_create_empty('custom_context_argument');
  }
  // Do whatever error checking is required, returning FALSE if it fails the test
  // Normally you'd check
  // for a missing object, one you couldn't create, etc.

  if (empty($arg)) {
    return FALSE;
  }
  $field_info = field_info_field($arg);
  if (empty($field_info)) {
    return ctools_context_create_empty('custom_context_argument');
  }

  return ctools_context_create('custom_context_argument', $field_info);
}