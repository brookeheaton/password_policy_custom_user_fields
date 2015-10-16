<?php
/** @file ... **/

$plugin = array(
  'admin form callback' => 'password_policy_user_fields_admin_form',
  'constraint callback' => 'password_policy_user_fields_constraint',
  'message' => 'Password must not contain user @user_fields',
  'prime value' => 'user_fields',
  'multi' => 'loop',
  'config' => array(
      'user_fields' => '',
  ),
);

/**
 * Admin form callback for user_fields constraint.
 */
function password_policy_user_fields_admin_form($form, &$form_state, $constraint) {
    $sub_form['user_fields_fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => t('User Fields'),
    );
    $instances = field_info_instances('user');
    $options = array();
    foreach ($instances['user'] as $name => $field) {
        if($field['widget']['module'] === 'text') {
            $options[$name] = $field['label'];
        }
        if (!empty($options)) {
            unset($form['user_fields']['#children'], $form['user_fields']['#prefix'], $form['user_fields']['#suffix']);
            $sub_form['user_fields_fieldset']['user_fields'] = array(
                '#title' => t('User Fields'),
                '#type' => 'checkboxes',
                '#default_value' => $constraint->config['user_fields'],
                '#options' => $options,
                '#description' => t('User Fields to be excluded from password string.'),
            );
        }
    };

  return $sub_form;
}

/**
 * Constraint callback for user_fields constraint.
 */
function password_policy_user_fields_constraint($password, $account, $constraint)
{
    $constraint_fields = $constraint->config['user_fields'];
    global $user;
    $user_fields = user_load($user->uid);
    if (empty($user_fields)) {
        return TRUE;
    }
    $result = TRUE;
    foreach ($constraint_fields as $value) {
        $field_value = $user_fields->{$value}['und']['0']['value'];
        if (!empty($field_value)) {
            $field_values[] = drupal_strtolower($field_value);
            foreach ($field_values as $field_value) {
                $password_lower = drupal_strtolower($password);
                if (strpos($password_lower, $field_value) !== FALSE) {
                    $result = FALSE;
                }
            }
        }
    }
    return $result;
}