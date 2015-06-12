<?php

/**
 * Implements hook_preprocess_node();
 */
function custom_bartik_subtheme_preprocess_node(&$vars) {
  //dpm($vars);
  $vars['theme_hook_suggestions'][] = 'node__'.$vars['node']->type.'__'.$vars['view_mode'];
}


function custom_bartik_subtheme_radio($vars) {
  $element = $vars['element'];
  $element ['#attributes']['type'] = 'radio';
  element_set_attributes($element, array('id', 'name', '#return_value' => 'value'));

  if (isset($element ['#return_value']) && $element ['#value'] !== FALSE && $element ['#value'] == $element ['#return_value']) {
    $element ['#attributes']['checked'] = 'checked';
  }
  _form_set_class($element, array('form-radio custom-class-form-radio'));

  return '<div class="form-radio-wrapper"><input' . drupal_attributes($element ['#attributes']) . ' /></div>';
}