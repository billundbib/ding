<?php
// $Id$

/**
 * @file categories.inc
 * Provides a category browser for the events overview page.
 */

/**
 * Callback function to supply a list of content types.
 *
 * This is only required to make CTools know that we're providing 
 * multiple types here (since we have no single => TRUE in the array).
 */
function ding_event_categories_ctools_content_types() {
  return array(
    'title' => t('Node'),
  );
}

/**
 * Callback function to supply a list of content types.
 */
function ding_event_categories_content_type_content_types() {
  $types = array(
    'categories_title' => array(
      'title' => t('Event categories'),
      'category' => t('Node'),
      'description' => t('Provides a selector for event categories.'),
    ),
  );
  return $types;
}

/**
 * Return the pane contents.
 */
function ding_event_categories_content_type_render($subtype, $conf, $panel_args, $context) {
  $block = new stdClass();

  if (isset($conf['vocabulary']) && $conf['vocabulary'] > 0) {
    $links = array();

    foreach (taxonomy_get_tree($conf['vocabulary'], 0, -1, 1) as $term) {
      $links[] = l($term->name, 'arrangementer/' . $term->tid);
    }

    if (!empty($links)) {
      $block->content = theme('item_list', $links);
    }
  }

  return $block;
}

/**
 * Return the pane titles.
 */
function ding_event_categories_content_type_admin_title($subtype, $conf, $context) {
  return t('Event categories', array('@s' => $context->identifier));
}

/**
 * Returns an edit form for the content type.
 *
 * We're not actually doing anything here, but we need to have this hook 
 * for this content type to work.
 */
function ding_event_categories_content_type_edit_form(&$form, &$form_state) {
  $vocabulary_options = array();
  foreach (taxonomy_get_vocabularies() as $voc) {
    $vocabulary_options[$voc->vid] = $voc->name;
  }

  $form['vocabulary'] = array(
    '#type' => 'select',
    '#title' => t('Vocabulary'),
    '#description' => t('Select the vocabulary used for event categories.'),
    '#options' => $vocabulary_options,
    '#default_value' => $form_state['conf']['vocabulary'],
  );

  return $form;
}

/**
 * Submit handler for the content type editing form.
 */
function ding_event_categories_content_type_edit_form_submit(&$form, &$form_state) {
  $form_state['conf']['vocabulary'] = $form_state['values']['vocabulary'];
}
