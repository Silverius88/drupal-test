<?php
/**
 * @file
 * demo_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function demo_feature_node_info() {
  $items = array(
    'article' => array(
      'name' => t('Статья'),
      'base' => 'node_content',
      'description' => t('Статья — это документ, который обычно используется для новостей, анонсов и любых других сообщений, для которых не задействованы другие типы документов. Этот тип документа также используют для ведения персонального блога. По умолчанию, документы этого типа выводятся на первую страницу сайта и их разрешено комментировать.'),
      'has_title' => '1',
      'title_label' => t('Заголовок'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
