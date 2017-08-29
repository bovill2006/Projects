<?php
session_start();
if(isset($_POST['submit'])){
error_reporting(E_STRICT | E_ALL);

$path = dirname(__FILE__) . '/dfpAPI/src';
set_include_path(get_include_path() . PATH_SEPARATOR . $path);

require_once 'Google/Api/Ads/Dfp/Lib/DfpUser.php';
require_once 'Google/Api/Ads/Dfp/Util/DateTimeUtils.php';
require_once 'Google/Api/Ads/Dfp/Util/StatementBuilder.php';
require_once 'Google/Api/Ads/Common/Util/MediaUtils.php';
require_once dirname(__FILE__) . '/../../../Common/ExampleUtils.php';

try {
  
    $user = new DfpUser();// user access
    $user->LogDefaults();
    
//---------------------------Order Creation --------------------------------------
    $orderService = $user->GetOrderService('v201502');
    $advertiserId = $_SESSION['id'];
    $salespersonId = '130940450';
    $traffickerId = '130940450';
    
    $orders = array(); 
    $order = new Order();
    $order->name = $_POST['Name'];
    $order->advertiserId = $advertiserId;
    $order->salespersonId = $salespersonId;
    $order->traffickerId = $traffickerId;

    
    $orders[] = $order ; 
    $orders= $orderService->createOrders($order); 
    
//--------------------------Order Creation---------------------------------------
  // Display results.
if (isset($order)) {
      $orderId = $orders[0]->id;

//--------------------------Targeting ad Unit/Sp---------------------------------  
$lineItemService = $user->GetService('LineItemService', 'v201502');

$targetedAdUnitIds = new AdUnitTargeting($_POST['type']);     
$inventoryTargeting = new InventoryTargeting();
$inventoryTargeting->targetedAdUnits = $targetedAdUnitIds; 
     
$targeting = new Targeting();
$targeting->inventoryTargeting = $inventoryTargeting;


$lineItems = array();     
      
      
//-------------------------Line item core----------------------------------------      
$lineItem = new LineItem();
$lineItem->name = 'Lineitem #' . uniqid();
$lineItem->orderId = $orderId; 
$lineItem->targeting = $targeting; //ad unit targeting
$lineItem->lineItemType = 'STANDARD'; // Type of line item
$lineItem->allowOverbook = 'TRUE';

$creativePlaceholder = new CreativePlaceholder();
if($_POST['type'] == 40331810){
$creativePlaceholder->size = new Size(900, 420, false);  
}else {
$creativePlaceholder->size = new Size(1080, 1920, false); 
}
$creativePlaceholder-> expectedCreativeCount = 1; 
$_SESSION['placeholder'] = $creativePlaceholder->id;


$lineItem->creativePlaceholders = array($creativePlaceholder);
$lineItem->creativeRotationType = 'EVEN';// Set the creative rotation type to even.
     
$lineItem->startDateTimeType = 'IMMEDIATELY';//start and end
$lineItem->endDateTime =DateTimeUtils::GetDfpDateTime(new DateTime('+1 month'));

    
//----------------------------------------cost-------------------------
    

if($_POST['unitType'] == 0){
$lineItem->costType = 'CPM';// The Cost
$lineItem->costPerUnit = new Money('USD', 7000000);
      
$goal = new Goal();// goal for users to reach
$goal->units = $_POST['limit'];
$goal->unitType = 'IMPRESSIONS';
}
    else if ($_POST['unitType'] == 1) 
{
$lineItem->costType = 'CPC';// The Cost
$lineItem->costPerUnit = new Money('USD', 750000);
      
$goal = new Goal();// goal for users to reach
$goal->units = $_POST['limit'];
$goal->unitType = 'CLICKS';
}

    
$goal->goalType = 'LIFETIME';
$lineItem->primaryGoal = $goal;
$lineItems[] = $lineItem;     
$lineItems = $lineItemService->createLineItems($lineItems);//creating line item


//---------------------------------Custom Critera------------------------------------------

$lineItemId = $lineItems[0]->id;
$_SESSION['lineitemid'] = $lineItemId; 

$age = $_POST['age'];
$cAge = new CustomCriteria();
$cAge->keyId = '207770';
$cAge->valueIds = $age;
$cAge->operator = 'IS'; 
    
    
$genderArray = $_POST['gender'];
$cGender = new CustomCriteria();
$cGender->keyId = '207530';
$cGender->valueIds = $genderArray;
$cGender->operator = 'IS';

    
$futureAva = $_POST['FutureAva'];
$cfAva = new CustomCriteria(); 
$cfAva->keyId = 208010;
$cfAva->valueIds = $futureAva;
$cfAva->operator = 'IS'; 

    
$groupAva = $_POST['GroupAva'];
$cgAva = new CustomCriteria();
$cgAva->keyId = '208130';
$cgAva->valueIds = $groupAva;
$cgAva->operator = 'IS'; 
    

$liveAva = array('207890', $_POST['LiveAva']);
$clAva = new CustomCriteria();
$clAva->keyId = $liveAva[0];
$clAva->valueIds = array($_POST['LiveAva']);
$clAva->operator = 'IS'; 

$ccSet = new CustomCriteriaSet(); 
$ccSet ->logicalOperator = 'AND'; 
$ccSet ->children = array($cAge, $cGender, $cfAva, $cgAva, $clAva);


$statementBuilder = new StatementBuilder();
  $statementBuilder->Where('id = :id')
      ->OrderBy('id ASC')
      ->Limit(1)
      ->WithBindVariableValue('id', $lineItemId);
    
  $results = $lineItemService->getLineItemsByStatement(
      $statementBuilder->ToStatement())->results; 
  $lt = $results[0];

    


    // Set the custom criteria targeting on the line item.
  $lt->targeting->customTargeting = $ccSet;

  // Update the line item on the server.
  $lts = $lineItemService->updateLineItems(array($lt));    

    foreach ($lts as $lineItem) {
    printf("Line item with ID %d was updated.\n", $lineItem->id);
    header ("refresh:1; url=CreateCreatives.php");
  }
      
//--------------------------Line Item Creation/targeting-----------------------------------      
          
  } 
} 
catch (OAuth2Exception $e) {
  ExampleUtils::CheckForOAuth2Errors($e);
} 
catch (ValidationException $e) {
  ExampleUtils::CheckForOAuth2Errors($e);
} 
catch (Exception $e) {
  print $e->getMessage() . "\n";
}
}

?>

