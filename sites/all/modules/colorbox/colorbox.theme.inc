<?php

/**
 * @file
 * Colorbox theme functions.
 */


/**
 * Returns HTML for an Colorbox image field formatter.
 *
 * @param $variables
 *   An associative array containing:
 *   - item: An array of image data.
 *   - image_style: An optional image style.
 *   - path: An array containing the link 'path' and link 'options'.
 *
 * @ingroup themeable
 */
function theme_colorbox_image_formatter($variables) {
  $item = $variables['item'];
  $node = $variables['node'];
  $field = $variables['field'];

  $image = array(
    'path' => $item['uri'],
    'alt' => $item['alt'],
    'title' => $item['title'],
    'style_name' => $variables['colorbox_node_style'],
  );

  // If the title is empty use alt or the node title in that order.
  if (empty($image['title'])) {
    if (!empty($image['alt'])) {
      $image['title'] = $image['alt'];
    }
    elseif (!empty($node->title)) {
      $image['title'] = $node->title;
    }
  }

  // Shorten the title for the example styles or when title shortening is active.
  $colorbox_style = variable_get('colorbox_style', 'default');
  $trim_length = variable_get('colorbox_title_trim_length', 75);
  if (((strpos($colorbox_style, 'colorbox/example') !== FALSE) || variable_get('colorbox_title_trim', 0)) && (drupal_strlen($item['title']) > $trim_length)) {
    $image['title'] = drupal_substr($item['title'], 0, $trim_length - 5) . '...';
  }

  // Build the gallery id.
  $nid = !empty($node->nid) ? $node->nid : 'nid';
  switch (variable_get('colorbox_imagefield_gallery', 1)) {
    case 0:
      $gallery_id = 'gallery-all';
      break;
    case 1:
      $gallery_id = 'gallery-' . $nid;
      break;
    case 2:
      $gallery_id = 'gallery-' . $nid . '-' . $field['field_name'];
      break;
    case 3:
      $gallery_id = '';
      break;
  }

  if ($style_name = $variables['colorbox_image_style']) {
    $path = image_style_url($style_name, $image['path']);
  }
  else {
    $path = file_create_url($image['path']);
  }

  return theme('colorbox_imagefield', array('image' => $image, 'path' => $path, 'title' => $image['title'], 'gid' => $gallery_id));
}

/**
 * Returns HTML for an image using a specific Colorbox image style.
 *
 * @param $variables
 *   An associative array containing:
 *   - style_name: The name of the style to be used to alter the original image.
 *   - path: The path of the image file relative to the Drupal files directory.
 *     This function does not work with images outside the files directory nor
 *     with remotely hosted images.
 *   - alt: The alternative text for text-based browsers.
 *   - title: The title text is displayed when the image is hovered in some
 *     popular browsers.
 *   - gid: Gallery id.
 *   - attributes: Associative array of attributes to be placed in the img tag.
 *   - getsize: If set to TRUE, the image's dimension are fetched and added as
 *     width/height attributes.
 *
 * @ingroup themeable
 */
function theme_colorbox_imagefield($variables) {
  if (!empty($variables['image']['style_name'])) {
    $image = theme('image_style', $variables['image']);
  }
  else {
    $image = theme('image', $variables['image']);
  }

  $options = array(
    'html' => TRUE,
    'attributes' => array(
      'title' => $variables['title'],
      'class' => 'colorbox imagefield imagefield-imagelink',
      'rel' => $variables['gid'],
    )
  );

  return l($image, $variables['path'], $options);
}

/**
 * Preprocess variables for the colorbox-insert-image.tpl.php file.
 */
function template_preprocess_colorbox_insert_image(&$variables) {
  $file = file_load($variables['item']['fid']);

  $variables['image_path'] = image_style_url($variables['item']['style_name'], $file->uri);

  if ($style_name = variable_get('colorbox_image_style', '')) {
    $variables['link_path'] = image_style_url($style_name, $file->uri);
  }
  else {
    $variables['link_path'] = file_create_url($file->uri);
  }

  $variables['class'] = $variables['widget']['settings']['insert_class'];

  $variables['gallery_id'] = '';
  switch (variable_get('colorbox_insert_gallery', 0)) {
    case 0:
    case 1:
    case 2:
      $variables['gallery_id'] = 'gallery-all';
      break;
    case 3:
      $variables['gallery_id'] = '';
      break;
  }
}
