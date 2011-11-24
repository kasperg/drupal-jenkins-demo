# Drupal Jenkins Demo

Drupal Jenkins Demo is an example which shows how [Drupal](http://drupal.org) projects can use continuous integration, [Phing](http://www.phing.info/trac/) and [Jenkins](http://jenkins-ci.org/).

[A Jenkins job for the project](http://jenkins.kasper.reload.dk:8080/job/drupal-demo/) has been setup using the [Jenkins job template for Drupal projects](http://reload.github.com/jenkins-drupal-template/).

## Contents
* Drupal 7.8
* [Token module](http://drupal.org/project/token): Used as an example module for static code analysis and unit tests
* Build file and configuration: [Phing Drupal Template](http://reload.github.com/phing-drupal-template/) is included as a submodule in `\build` and [configured to check the Token module](https://github.com/kasperg/drupal-jenkins-demo/blob/master/build.properties)
* This README file

## Related projects
* [Phing Drupal Template](http://reload.github.com/phing-drupal-template/): Template Phing build.xml file for Drupal projects
* [Jenkins job template for Drupal projects](http://reload.github.com/jenkins-drupal-template/): A standard Jenkins job template for Drupal projects
