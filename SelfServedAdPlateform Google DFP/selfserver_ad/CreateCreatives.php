<?php
session_start();

error_reporting(E_STRICT | E_ALL);

// You can set the include path to src directory or reference
// DfpUser.php directly via require_once.
// $path = '/path/to/dfp_api_php_lib/src';
$path = dirname(__FILE__) . '/dfpAPI/src';
set_include_path(get_include_path() . PATH_SEPARATOR . $path);

require_once 'Google/Api/Ads/Dfp/Lib/DfpUser.php';
require_once 'Google/Api/Ads/Common/Util/MediaUtils.php';
require_once dirname(__FILE__) . '/../../../Common/ExampleUtils.php';

// Set the ID of the advertiser (company) that all creatives will be
// assigned to.
$advertiserId = $_SESSION['id'];
echo $advertiserId; 

try {
  // Get DfpUser from credentials in "../auth.ini"
  // relative to the DfpUser.php file's directory.
  $user = new DfpUser();

  // Log SOAP XML request and response.
  $user->LogDefaults();

  // Get the CreativeService.
  $creativeService = $user->GetService('CreativeService', 'v201502');
  $licaService = $user->GetService('LineItemCreativeAssociationService', 'v201502');

  // Create an array to store local image creative objects.
  $imageCreatives = array();

  for ($i = 0; $i < 1; $i++) {
    // Create creative size.
    $size = new Size(1080, 1920, false);

    // Create an image creative.
    $imageCreative = new ImageCreative();
    $imageCreative->name = 'Image creative #' . $i;
    $imageCreative->advertiserId = $advertiserId;
    $imageCreative->destinationUrl = 'http://google.com';
    $imageCreative->size = $size;

    // Create image asset.
    $creativeAsset = new CreativeAsset();
    $creativeAsset->fileName = 'image.jpg';
    $creativeAsset->assetByteArray =
        MediaUtils::GetBase64Data('http://geekongadgets.com/wp-content/uploads/2014/05/concrete-texture-abstract-mobile-wallpaper-1080x1920-4590-4143710250.jpg');
    $creativeAsset->size = $size;
    $imageCreative->primaryImageAsset = $creativeAsset;

    $imageCreatives[] = $imageCreative;
  }

  // Create the image creatives on the server.
  $imageCreatives = $creativeService->createCreatives($imageCreatives);

  // Display results.
  if (isset($imageCreatives)) {
      
      $lineItemId = $_SESSION['lineitemid'];
      $creativeId = $imageCreatives[0]->id;
      
      $lica = new LineItemCreativeAssociation();
      $lica->creativeId = $creativeId;
      $lica->lineItemId = $lineItemId;

      $licas = array($lica);

      $licas = $licaService->createLineItemCreativeAssociations($licas);
      
      
  } else {
    printf("No creatives created.\n");
  }
    header ("refresh:2; url=account.php");
} catch (OAuth2Exception $e) {
  ExampleUtils::CheckForOAuth2Errors($e);
} catch (ValidationException $e) {
  ExampleUtils::CheckForOAuth2Errors($e);
} catch (Exception $e) {
  printf("%s\n", $e->getMessage());
}

