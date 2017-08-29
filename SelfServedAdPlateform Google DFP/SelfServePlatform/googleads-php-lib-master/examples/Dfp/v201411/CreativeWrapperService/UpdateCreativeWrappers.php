<?php
/**
 * This example updates a creative wrapper's wrapping order to 'OUTER'. To
 * determine which creative wrappers exist, run GetAllCreativeWrappers.php.
 *
 * Tags: CreativeWrapperService.getCreativeWrappersByStatement
 * Tags: CreativeWrapperService.updateCreativeWrappers
 *
 * PHP version 5
 *
 * Copyright 2014, Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @package    GoogleApiAdsDfp
 * @subpackage v201411
 * @category   WebServices
 * @copyright  2014, Google Inc. All Rights Reserved.
 * @license    http://www.apache.org/licenses/LICENSE-2.0 Apache License,
 *             Version 2.0
 * @author     Vincent Tsao
 */
error_reporting(E_STRICT | E_ALL);

// You can set the include path to src directory or reference
// DfpUser.php directly via require_once.
// $path = '/path/to/dfp_api_php_lib/src';
$path = dirname(__FILE__) . '/../../../../src';
set_include_path(get_include_path() . PATH_SEPARATOR . $path);

require_once 'Google/Api/Ads/Dfp/Lib/DfpUser.php';
require_once 'Google/Api/Ads/Dfp/Util/StatementBuilder.php';
require_once dirname(__FILE__) . '/../../../Common/ExampleUtils.php';

// Set the ID of the creative wrapper to update.
$creativeWrapperId = 'INSERT_CREATIVE_WRAPPER_ID_HERE';

try {
  // Get DfpUser from credentials in "../auth.ini"
  // relative to the DfpUser.php file's directory.
  $user = new DfpUser();

  // Log SOAP XML request and response.
  $user->LogDefaults();

  // Get the CreativeWrapperService.
  $creativeWrapperService = $user->GetService('CreativeWrapperService', 'v201411');

  // Create a statement to select a single creative wrapper by ID.
  $statementBuilder = new StatementBuilder();
  $statementBuilder->Where('id = :id')
      ->OrderBy('id ASC')
      ->Limit(1)
      ->WithBindVariableValue('id', $creativeWrapperId);

  // Get the creative wrapper.
  $page = $creativeWrapperService->getCreativeWrappersByStatement(
      $statementBuilder->ToStatement());
  $creativeWrapper = $page->results[0];

  // Update the creative wrapper ordering.
  $creativeWrapper->ordering = 'OUTER';

  // Update the creative wrapper on the server.
  $creativeWrappers =
      $creativeWrapperService->updateCreativeWrappers(array($creativeWrapper));

  foreach ($creativeWrappers as $updatedCreativeWrapper) {
    printf("Creative wrapper with ID %d, and wrapping order '%s' was "
        . "updated.\n", $updatedCreativeWrapper->id,
        $updatedCreativeWrapper->ordering);
  }
} catch (OAuth2Exception $e) {
  ExampleUtils::CheckForOAuth2Errors($e);
} catch (ValidationException $e) {
  ExampleUtils::CheckForOAuth2Errors($e);
} catch (Exception $e) {
  printf("%s\n", $e->getMessage());
}

