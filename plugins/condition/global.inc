<?php
/**
 * @file
 * Global condition for Password Policy module.
 */

$plugin = array(
  'admin form callback' => 'password_policy_global_admin_form',
  'condition callback' =>  'password_policy_global_condition',
  'prime value' => 'global_char_count',
  'config' => array(
    'global' => FALSE,
  ),
);

/**
 * Admin form callback for global condition.
 */
function password_policy_global_admin_form($form, &$form_state, $condition) {
  $sub_form['global_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global'),
  );
  $sub_form['global_fieldset']['global'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled always'),
    '#default_value' => $condition->config['global'],
  );
  return $sub_form;
}

/**
 * Condition callback for global condition.
 */
function password_policy_global_condition($account, $condition) {
  return $condition->config['global'];
}