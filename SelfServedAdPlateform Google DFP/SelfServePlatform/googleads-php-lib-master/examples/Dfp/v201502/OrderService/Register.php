<?php
$conn = mysqli_connect("localhost", "root", "password", "test") or die("Error" . mysqli_error($conn));

echo "Connected successfully, \n";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
error_reporting(E_STRICT | E_ALL);
// You can set the include path to src directory or reference
// DfpUser.php directly via require_once.
// $path = '/path/to/dfp_api_php_lib/src';
$path = dirname(__FILE__) . '/../../../../src';
set_include_path(get_include_path() . PATH_SEPARATOR . $path);

require_once 'Google/Api/Ads/Dfp/Lib/DfpUser.php';
require_once dirname(__FILE__) . '/../../../Common/ExampleUtils.php';

if(isset($_POST['submit'])) {
    
try {
  $user = new DfpUser();
  $user->LogDefaults();
  $companyService = $user->GetService('CompanyService', 'v201502');
  $companies = array(); 
    
    $company = new Company();
    $company->name = $_POST['company'];
    $company->type = 'ADVERTISER';
    $companies[] = $company; 
    

  $companies = $companyService->createCompanies($companies);
    
    if (isset($companies)){
        
    foreach ($companies as $company){    
    $sSql = "INSERT INTO users
		(username, password, email, id, company)
		 VALUES ('$_POST[username]', '".sha1(mysqli_real_escape_string($conn, $_POST['password']))."', '$_POST[email]', '$company->id', '$_POST[company]')";
      echo $sSql;
	$conn -> query($sSql);
    }
}

} catch (OAuth2Exception $e) {
  ExampleUtils::CheckForOAuth2Errors($e);
} catch (ValidationException $e) {
  ExampleUtils::CheckForOAuth2Errors($e);
} catch (Exception $e) {
  print $e->getMessage() . "\n";
}


	
}
?>