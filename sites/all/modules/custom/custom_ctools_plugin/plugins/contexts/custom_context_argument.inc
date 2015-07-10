<?php

/**
 * @file
 * Create custom context from an argument.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Custom context argument"),
  'description' => t('Custom context created from an argument.'),
  'context' => 'create_custom_context_argument',  // func to create context
  'context name' => 'custom_context_argument',
  'edit form' => 'custom_context_argument_settings_form',
  'defaults' => array('field_name' => ''),
  'keyword' => 'custom_context_argument',
  'convert list' => 'custom_context_argument_convert_list',
  'convert' => 'custom_context_argument_convert',
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter some field name.'),
  ),
);

/**
 * Create a context, either from manual configuration or from an argument on the URL.
 *
 * @param $empty
 *   If true, just return an empty context.
 * @param $data
 *   If from settings form, an array as from a form. If from argument, a string.
 * @param $conf
 *   TRUE if the $data is coming from admin configuration, FALSE if it's from a URL arg.
 *
 * @return
 *   a Context object/
 */
function create_custom_context_argument($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context('custom_context_argument');
  $context->plugin = 'custom_context_argument';

  if ($empty) {
    return $context;
  }

  if ($conf) {
    $field_info = field_info_field($data['field_name']);
    if (!empty($field_info)) {
      $context->data = new stdClass();
      $context->data->field_id = isset($field_info['id']) ? $field_info['id'] : '';
      $context->data->field_type = isset($field_info['type']) ? $field_info['type'] : '';
      $context->title = t("Custom context from config");
      return $context;
    }
  }

  if (!empty($data)) {
    $context->data = new stdClass();
    $context->data->field_id = isset($data['id']) ? $data['id'] : '';
    $context->data->field_type = isset($data['type']) ? $data['type'] : '';
    $context->title = t("Custom context not from config");
    return $context;
  }
}

/**
 * Settings form.
 */
function custom_context_argument_settings_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['field_name'] = array(
    '#title' => t('Enter a field name'),
    '#type' => 'textfield',
    '#default_value' => isset($conf['field_name']) ? $conf['field_name'] : '',
    '#maxlength' => 128,
    '#weight' => -10,
  );
  return $form;
}

/**
 * Validate a settings form.
 */
function custom_context_argument_settings_form_validate($form, &$form_state) {
  $field_info = field_info_field($form_state['values']['field_name']);
  if (empty($field_info)) {
    form_error($form['field_name'], t('Field is not found. Please enter another field name.'));
  }
}

/**
 * Submit settings form.
 */
function custom_context_argument_settings_form_submit($form, &$form_state) {
  $form_state['conf']['field_name'] = $form_state['values']['field_name'];
}

/**
 * Provide a list of sub-keywords.
 *
 * This is used to provide keywords from the context for use in a content type,
 * pane, etc.
 */
function custom_context_argument_convert_list() {
  return array(
    'field_id' => t('Field ID'),
    'field_type' => t('Field type'),
  );
}

/**
 * Convert a context into a string to be used as a keyword by content types, etc.
 */
function custom_context_argument_convert($context, $type) {
  switch ($type) {
    case 'field_id':
      return $context->data->field_id;
    case 'field_type':
      return $context->data->field_type;
  }
}