<?php
/**
 * @file
 * Letter count constraint for Password Policy module.
 */

$plugin = array(
  'admin form callback' => 'password_policy_alpha_count_admin_form',
  'constraint callback' =>  'password_policy_alpha_count_constraint',
  'message' => 'Password must have at least alpha_count letters',
  'default' => 0,
);

/**
 * Admin form callback for letter count constraint.
 */
function password_policy_alpha_count_admin_form($form, &$form_state, $constraint) {
  $sub_form['alpha_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum letters'),
    '#default_value' => $constraint->config['alpha_count'],
    '#description' => "Password will be required to have this many Letters",
  );

  return $sub_form;
}

/**
 * Constraint callback for letter count constraint.
 */
function password_policy_alpha_count_constraint($password, $account, $constraint) {
  $count = $constraint->config['alpha_count'];
  $regex_string = "/.*";
  if ($count && $count > 0) {
    for ($i = 1 ; $i<=$count; $i++) {
      $regex_string .='[a-zA-Z].*';
    }
  }

  $regex_string .= '/';
  return preg_match($regex_string, $password);
}