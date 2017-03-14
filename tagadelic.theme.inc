<?php
/**
 * @file
 * Theme functions for tagadelic module.
 */

/**
 * Theme function that renders an entry in tagadelic/list/ views.
 *
 * @param $vocabulary
 *   A full vocabulary object.
 * @param $tags
 *   An array with weighted tag objects.
 * @ingroup themable
 */
function theme_tagadelic_list_box(array $vars) {
  $vocabulary = $vars['vocabulary'];
  $tags = $vars['tags'];

  // The theme function is sometimes used for multiple vocabularies, so
  // expects an array of vocabulary names.
  $vocs = array($vocabulary->machine_name);
  $content = theme('tagadelic_weighted', array('terms' => $tags, 'vocs' => $vocs));
  $output = '';
  if ($vocabulary->description) {
    $content = '<h2></h2><div>' . $vocabulary->description . '</div>' . $content;
  }
  $output .= '<h2>' . $vocabulary->name . '</h2><div>' . $content . '</div>';

  return $output;
}

/**
 * Theme function that renders the HTML for the tags.
 *
 * @param array $vars
 *   An array, with the first vars element key 'terms' which should have an
 *   array for each term, and the second vars element key 'voc' which should be
 *   an array of vocabulary names.
 *
 * @return string
 *   The output.
 *
 * @ingroup themable
 */
function theme_tagadelic_weighted(array $vars) {
  $terms = $vars['terms'];
  $vocs = $vars['vocs'];
  $output = '';

  foreach ($terms as $term) {
    $output .= l($term->name, 'taxonomy/term/' . $term->tid, array(
      'attributes' => array(
        'class' => array("tagadelic", "level" . $term->weight),
        'rel' => 'tag',
        'title'  => $term->description,
        )
      )
    ) . " \n";
  }

  // @todo Make more link work with page limits, and multiple vocabularies.
  //if (count($terms) >= config_get('tagadelic.settings', 'block_tags_' . $vars['voc']->machine_name)) {
    $more_link_url_arg = implode(",", $vocs);
    $output .= theme('more_link', array('title' => t('more tags'), 'url' => "tagadelic/chunk/{$more_link_url_arg}"));
  //}

  return $output;
}
