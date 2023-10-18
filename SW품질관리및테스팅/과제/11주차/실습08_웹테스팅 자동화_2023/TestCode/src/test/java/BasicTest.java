import org.junit.BeforeClass;
import org.junit.Test;
import org.openqa.selenium.By;
import org.openqa.selenium.StaleElementReferenceException;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;

import static junit.framework.TestCase.assertEquals;

import java.util.concurrent.TimeUnit;

import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.Select;
import org.openqa.selenium.support.ui.WebDriverWait;

public class BasicTest extends TestHelper {


    private String username = "zelda";
    private String password = "1234";
    
    @BeforeClass
    public static void registerTest() throws InterruptedException
    {
		System.setProperty("webdriver.chrome.driver", "C:\\Users\\kocan\\OneDrive - dongguk.edu\\컴공\\SW품질관리및테스팅\\과제\\11주차\\chromedriver_win32\\chromedriver.exe");
		WebDriver driver = new ChromeDriver();
		driver.manage().timeouts().implicitlyWait(10, TimeUnit.SECONDS);
    	driver.get("http://127.0.0.1:3000/admin");
    	driver.manage().window().maximize();
	   	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
	   	Thread.sleep(4000);
	   	driver.findElement(By.id("user_name")).sendKeys("zelda");
	   	driver.findElement(By.id("user_password")).sendKeys("1234");
	   	driver.findElement(By.id("user_password_confirmation")).sendKeys("1234");
	   	driver.findElement(By.xpath("//*[@id=\"register_button\"]/input")).click();
	   	Thread.sleep(4000);
	   	String expected = "User zelda was successfully created.";
	   	String atcual = driver.findElement(By.id("notice")).getText();
	   	assertEquals(expected, atcual);
	   	
	    driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[1]/a")).click();
	    Thread.sleep(4000);
	    expected = "Logged in user: zelda Edit Delete";
	    atcual = driver.findElement(By.id("zelda")).getText();
	    assertEquals(expected, atcual);
	    driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
	    driver.close();
    }
    
    @Test
    public void titleExistsTest() throws InterruptedException{
        String expectedTitle = "ST Online Store";
        String actualTitle = driver.getTitle();
        Thread.sleep(4000);
        assertEquals(expectedTitle, actualTitle);
    }

    @Test
    public void AdminTest() throws InterruptedException
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	Thread.sleep(4000);
    	String expected = "Welcome to Admin Site";
    	String atcual = driver.findElement(By.id("Admin")).getText();
    	assertEquals(expected, atcual);
    }
    
    @Test
    public void additionalRegisterTest() throws InterruptedException
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
    	Thread.sleep(4000);
    	driver.findElement(By.id("user_name")).sendKeys("test");
    	driver.findElement(By.id("user_password")).sendKeys("1234");
    	driver.findElement(By.id("user_password_confirmation")).sendKeys("1234");
    	driver.findElement(By.xpath("//*[@id=\"register_button\"]/input")).click();
    	
    	Thread.sleep(4000);
    	String expected = "User test was successfully created.";
    	String atcual = driver.findElement(By.id("notice")).getText();
    	assertEquals(expected, atcual);
    	
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[1]/a")).click();
    	Thread.sleep(4000);
    	expected = "Logged in user: test Edit Delete";
    	atcual = driver.findElement(By.id("test")).getText();
    	assertEquals(expected, atcual);
    	driver.findElement(By.xpath("//*[@id=\"test\"]/a[2]")).click();    	
    }
    
    @Test
    public void Register_omitForm_Test() throws InterruptedException
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
    	Thread.sleep(4000);
    	driver.findElement(By.id("user_name")).sendKeys("");
    	driver.findElement(By.id("user_password")).sendKeys("");
    	driver.findElement(By.id("user_password_confirmation")).sendKeys("");
    	driver.findElement(By.xpath("//*[@id=\"register_button\"]/input")).click();
    	
    	Thread.sleep(4000);
    	String expected = "Name can't be blank";
    	String atcual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[2]/form/div[1]/ul/li[1]")).getText();
    	assertEquals(expected, atcual);
    	
    	Thread.sleep(4000);
    	expected = "Password can't be blank";
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[2]/form/div[1]/ul/li[2]")).getText();
    	assertEquals(expected, atcual);
    	
    	driver.findElement(By.id("user_name")).sendKeys("test");
    	driver.findElement(By.id("user_password")).sendKeys("1234");
    	driver.findElement(By.id("user_password_confirmation")).sendKeys("");
    	driver.findElement(By.xpath("//*[@id=\"register_button\"]/input")).click();
    	
    	Thread.sleep(4000);
    	expected = "Password confirmation doesn't match Password";
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[2]/form/div[1]/ul/li")).getText();
    	assertEquals(expected, atcual);    	
    }
    
    @Test
    public void deleteAccountTest() throws InterruptedException
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
    	driver.findElement(By.id("user_name")).sendKeys("test");
    	driver.findElement(By.id("user_password")).sendKeys("1234");
    	driver.findElement(By.id("user_password_confirmation")).sendKeys("1234");
    	driver.findElement(By.xpath("//*[@id=\"register_button\"]/input")).click();

    	Thread.sleep(4000);
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[1]/a")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/p[3]/a[2]")).click();
    	
    	Thread.sleep(4000);
    	String expected = "User was successfully deleted.";
    	String atcual = driver.findElement(By.id("notice")).getText();
    	assertEquals(expected, atcual);
    	
    	driver.findElement(By.xpath("/html/body/div[2]/div/ul/li[2]/a")).click();
    	Thread.sleep(4000);
    	driver.findElement(By.id("name")).sendKeys("test");
    	driver.findElement(By.id("password")).sendKeys("1234");
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[2]/form/div[3]/input")).click();  
    	Thread.sleep(4000);
    	expected = "Invalid user/password combination";
    	atcual = driver.findElement(By.id("notice")).getText();
    	assertEquals(expected, atcual);	   	
    }
    
    @Test
    public void logoutTest() throws InterruptedException
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[2]/a")).click();
    	driver.findElement(By.id("name")).sendKeys(username);
    	driver.findElement(By.id("password")).sendKeys(password);
    	driver.findElement(By.xpath("//*[@id=\"login_button\"]/input")).click();
    	
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
    	Thread.sleep(4000);
    	String expected = "Login";
    	String atcual = driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[2]/a")).getText();
    	assertEquals(expected, atcual);
    }
    
    @Test
    public void loginTest() throws InterruptedException
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[2]/a")).click();
    	Thread.sleep(4000);
    	driver.findElement(By.id("name")).sendKeys(username);
    	driver.findElement(By.id("password")).sendKeys(password);
    	driver.findElement(By.xpath("//*[@id=\"login_button\"]/input")).click();
    	Thread.sleep(4000);
    	String expected = "Logout";
    	String atcual = driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).getText();
    	assertEquals(expected, atcual);
    	
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[1]/a")).click();
    	Thread.sleep(4000);
    	expected = "Logged in user: zelda Edit Delete";
    	atcual = driver.findElement(By.id(username)).getText();
    	assertEquals(expected, atcual);
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
    }
      
    
    @Test
    public void addProductTest() throws InterruptedException
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[2]/a")).click();
    	driver.findElement(By.id("name")).sendKeys(username);
    	driver.findElement(By.id("password")).sendKeys(password);
    	driver.findElement(By.xpath("//*[@id=\"login_button\"]/input")).click();
    	
    	driver.findElement(By.xpath("//*[@id=\"new_product_div\"]/a")).click();
    	Thread.sleep(4000);
    	driver.findElement(By.id("product_title")).sendKeys("Calculator");
    	driver.findElement(By.id("product_description")).sendKeys("this is Calculator");
    	Select drpType = new Select(driver.findElement(By.id("product_prod_type")));
    	drpType.selectByVisibleText("Other");
    	driver.findElement(By.id("product_price")).sendKeys("10000");
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[2]/a"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[2]/a")).click();
    	assertEquals("Title: Calculator", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[2]")).getText());
    	assertEquals("Description: this is Calculator", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[3]")).getText());
    	assertEquals("Type: Other", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[4]")).getText());
    	assertEquals("Price: €10,000.00", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[5]")).getText());
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/div/a[2]")).click();
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[4]/a"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[4]/a")).click();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
    }
    
    @Test
    public void addProduct_omitForm_Test() throws InterruptedException
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[2]/a")).click();
    	driver.findElement(By.id("name")).sendKeys(username);
    	driver.findElement(By.id("password")).sendKeys(password);
    	driver.findElement(By.xpath("//*[@id=\"login_button\"]/input")).click();
    	
    	driver.findElement(By.xpath("//*[@id=\"new_product_div\"]/a")).click();
    	Thread.sleep(4000);
    	driver.findElement(By.id("product_title")).sendKeys("");
    	driver.findElement(By.id("product_description")).sendKeys("");
    	Select drpType = new Select(driver.findElement(By.id("product_prod_type")));
    	drpType.selectByVisibleText("Select product type");
    	driver.findElement(By.id("product_price")).sendKeys("");
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();
    	
    	assertEquals("Title can't be blank", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li[1]")).getText());
    	assertEquals("Description can't be blank", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li[2]")).getText());
    	assertEquals("Select Prod type", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li[3]")).getText());
    	assertEquals("Price is not a number", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li[4]")).getText());
    }
    
    @Test
    public void editProductTest() throws InterruptedException
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[2]/a")).click();
    	driver.findElement(By.id("name")).sendKeys(username);
    	driver.findElement(By.id("password")).sendKeys(password);
    	driver.findElement(By.xpath("//*[@id=\"login_button\"]/input")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("//*[@id=\"new_product_div\"]/a")).click();
    	driver.findElement(By.id("product_title")).sendKeys("Calculator");
    	driver.findElement(By.id("product_description")).sendKeys("this is Calculator");
    	Select drpType = new Select(driver.findElement(By.id("product_prod_type")));
    	drpType.selectByVisibleText("Other");
    	driver.findElement(By.id("product_price")).sendKeys("10000");
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[3]/a")).click();
    	driver.findElement(By.id("product_title")).clear();
    	driver.findElement(By.id("product_title")).sendKeys("New Calculator");
    	
    	driver.findElement(By.id("product_description")).clear();
    	driver.findElement(By.id("product_description")).sendKeys("Calculator");
    	
    	drpType = new Select(driver.findElement(By.id("product_prod_type")));
    	drpType.selectByVisibleText("Books");
    	
    	driver.findElement(By.id("product_price")).clear();
    	driver.findElement(By.id("product_price")).sendKeys("20000");
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();
    	driver.findElement(By.xpath("//*[@id=\"main\"]/div/div/a[2]")).click();
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[2]/a"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[2]/a")).click();
    	
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/p[2]"))
    			);
    	assertEquals("Title: New Calculator", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[2]")).getText());
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/p[3]"))
    			);
    	assertEquals("Description: Calculator", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[3]")).getText());
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/p[4]"))
    			);
    	assertEquals("Type: Books", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[4]")).getText());
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/p[5]"))
    			);
    	assertEquals("Price: €20,000.00", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[5]")).getText());
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/div/a[2]")).click();
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[4]/a"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[4]/a")).click();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
    }
     
    @Test
    public void editProduct_omitForm_Test() throws InterruptedException
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[2]/a")).click();
    	driver.findElement(By.id("name")).sendKeys(username);
    	driver.findElement(By.id("password")).sendKeys(password);
    	driver.findElement(By.xpath("//*[@id=\"login_button\"]/input")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("//*[@id=\"new_product_div\"]/a")).click();
    	driver.findElement(By.id("product_title")).sendKeys("Calculator");
    	driver.findElement(By.id("product_description")).sendKeys("this is Calculator");
    	Select drpType = new Select(driver.findElement(By.id("product_prod_type")));
    	drpType.selectByVisibleText("Other");
    	driver.findElement(By.id("product_price")).sendKeys("10000");
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[3]/a")).click();
    	driver.findElement(By.id("product_title")).clear();   	
    	driver.findElement(By.id("product_description")).clear();
    	driver.findElement(By.id("product_price")).clear();
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();
    	
    	assertEquals("Title can't be blank", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li[1]")).getText());
    	assertEquals("Description can't be blank", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li[2]")).getText());
    	assertEquals("Price is not a number", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li[3]")).getText());
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/div/a"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/div/a")).click();
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[4]/a"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[4]/a")).click();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
    }
    
    @Test
    public void deleteProductTest() throws InterruptedException
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[2]/a")).click();
    	driver.findElement(By.id("name")).sendKeys(username);
    	driver.findElement(By.id("password")).sendKeys(password);
    	driver.findElement(By.xpath("//*[@id=\"login_button\"]/input")).click();
    	
    	driver.findElement(By.xpath("//*[@id=\"new_product_div\"]/a")).click();
    	Thread.sleep(4000);
    	driver.findElement(By.id("product_title")).sendKeys("Calculator");
    	driver.findElement(By.id("product_description")).sendKeys("this is Calculator");
    	Select drpType = new Select(driver.findElement(By.id("product_prod_type")));
    	drpType.selectByVisibleText("Other");
    	driver.findElement(By.id("product_price")).sendKeys("10000");
    	driver.findElement(By.xpath("//*[@id=\"new_product\"]/div[5]/input")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[4]/a")).click();
    	
    	String expected = "Product was successfully destroyed.";
    	String atcual = driver.findElement(By.id("notice")).getText();
    	assertEquals(expected, atcual);
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
    }
    
    @Test
    public void addProductToCartTest() throws InterruptedException
    {
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[4]/div[2]/form/input[1]")).click();
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[5]/div[2]/form/input[1]")).click();
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[6]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	String expected = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/h3/a")).getText();
    	Thread.sleep(4000);
    	String atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[2]")).getText();
    	assertEquals(expected, atcual);
    	Thread.sleep(4000);
    	expected = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/span")).getText();;
    	Thread.sleep(4000);
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[3]")).getText();
    	assertEquals(expected, atcual);

    	Thread.sleep(4000);
    	expected = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[4]/h3/a")).getText();;
    	Thread.sleep(4000);
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[2]/td[2]")).getText();
    	assertEquals(expected, atcual);
    	Thread.sleep(4000);
    	expected = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[4]/div[2]/span")).getText();;
    	Thread.sleep(4000);
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[2]/td[3]")).getText();
    	assertEquals(expected, atcual);

    	Thread.sleep(4000);
    	expected = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[5]/h3/a")).getText();;
    	Thread.sleep(4000);
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[3]/td[2]")).getText();
    	assertEquals(expected, atcual);
    	Thread.sleep(4000);
    	expected = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[5]/div[2]/span")).getText();;
    	Thread.sleep(4000);
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[3]/td[3]")).getText();
    	assertEquals(expected, atcual);

    	Thread.sleep(4000);
    	expected = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[6]/h3/a")).getText();;
    	Thread.sleep(4000);
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[4]/td[2]")).getText();
    	assertEquals(expected, atcual);
    	Thread.sleep(4000);
    	expected = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[6]/div[2]/span")).getText();;
    	Thread.sleep(4000);
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[4]/td[3]")).getText();
    	assertEquals(expected, atcual);
    	
    	Thread.sleep(4000);
    	expected = "€107.99";
    	Thread.sleep(4000);
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[5]/td[2]")).getText();
    	assertEquals(expected, atcual);
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[6]/a")).click();
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[6]/a")).click();
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[6]/a")).click();
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[6]/a")).click();
    }
    
    @Test
    public void addAmountProductTest() throws InterruptedException
    {
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[5]/a")).click();
    	
    	Thread.sleep(4000);
    	String expected = "2×";
    	String atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[1]")).getText();
    	assertEquals(expected, atcual);
    	
    	Thread.sleep(4000);
    	expected = "€52.00";
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[3]")).getText();
    	assertEquals(expected, atcual);
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[4]/a")).click();
    	
    	Thread.sleep(4000);
    	expected = "1×";
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[1]")).getText();
    	assertEquals(expected, atcual);
    	
    	Thread.sleep(4000);
    	expected = "€26.00";
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[3]")).getText();
    	assertEquals(expected, atcual);
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();
    	Thread.sleep(4000);
    	expected = "2×";
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[1]")).getText();
    	assertEquals(expected, atcual);
    	
    	Thread.sleep(4000);
    	expected = "€52.00";
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[3]")).getText();
    	assertEquals(expected, atcual);
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[6]/a")).click();
    }
    
    @Test
    public void deleteProductfromCartTest() throws InterruptedException
    {
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[4]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[5]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[6]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[6]/a")).click();
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[6]/a")).click();
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[6]/a")).click();
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[6]/a")).click();
    	
    	String expected = "Ooo";
    	String atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div")).getText();
    	assertEquals(expected, atcual);
    }
    
    @Test
    public void EmptyCartTest() throws InterruptedException
    {
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[4]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[5]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[6]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/form[1]/input[2]")).click();
    	
    	String expected = "Ooo";
    	String atcual = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div")).getText();
    	assertEquals(expected, atcual);
    }
    
    @Test
    public void searchProductTest() throws InterruptedException
    {
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[1]/form/input")).sendKeys("B45593 Sunglasses");
    	
    	String expected = "B45593 Sunglasses";
    	String atcual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/h3/a")).getText();
    	assertEquals(expected, atcual);
    }
    
    @Test
    public void filterProductTest() throws InterruptedException
    {
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[2]/div/ul/li[2]/a")).click();
    	
    	Thread.sleep(4000);
    	String expected = "Category: Sunglasses";
    	String atcual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[2]/p[4]")).getText();
    	assertEquals(expected, atcual);    	
    	
    	Thread.sleep(4000);
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/p[4]")).getText();
    	assertEquals(expected, atcual);    	
    	
    	Thread.sleep(4000);
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[4]/p[4]")).getText();
    	assertEquals(expected, atcual);
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[2]/div/ul/li[3]/a")).click();
    	
    	Thread.sleep(4000);
    	expected = "Category: Books";
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[2]/p[4]")).getText();
    	assertEquals(expected, atcual);
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[2]/div/ul/li[4]/a")).click();
    	
    	Thread.sleep(4000);
    	expected = "Other";
    	atcual = driver.findElement(By.xpath("/html/body/div[4]/div[2]")).getText();
    	assertEquals(expected, atcual);    	
    }
    
    @Test
    public void purchaseProductTest() throws InterruptedException
    {
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();	
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[4]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[5]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[6]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	String expected_price1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[3]")).getText();
    	String expected_price2 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[2]/td[3]")).getText();
    	String expected_price3 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[3]/td[3]")).getText();
    	String expected_price4 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[4]/td[3]")).getText();
    	
    	Thread.sleep(4000);
    	String expected_amount1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[1]")).getText();
    	String expected_amount2 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[2]/td[1]")).getText();
    	String expected_amount3 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[3]/td[1]")).getText();
    	String expected_amount4 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[4]/td[1]")).getText();
    	
    	String expected_total = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[5]/td[2]")).getText();
    	
    	Thread.sleep(4000);
    	String expected_name1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[2]")).getText();
    	String expected_name2 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[2]/td[2]")).getText();
    	String expected_name3 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[3]/td[2]")).getText();
    	String expected_name4 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[4]/td[2]")).getText();
    	
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/form[2]/input")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.id("order_name")).sendKeys("test");
    	driver.findElement(By.id("order_address")).sendKeys("test address");
    	driver.findElement(By.id("order_email")).sendKeys("test@test.com");
    	Select drpType = new Select(driver.findElement(By.id("order_pay_type")));
    	drpType.selectByVisibleText("Check");
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();    	
    	
    	Thread.sleep(4000);
    	String actual_price1 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[3]")).getText();
    	Thread.sleep(4000);
    	String actual_price2 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[2]/td[3]")).getText();
    	Thread.sleep(4000);
    	String actual_price3 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[3]/td[3]")).getText();
    	Thread.sleep(4000);
    	String actual_price4 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[4]/td[3]")).getText();
    	
    	Thread.sleep(4000);
    	String actual_amount1 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[1]")).getText();
    	Thread.sleep(4000);
    	String actual_amount2 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[2]/td[1]")).getText();
    	Thread.sleep(4000);
    	String actual_amount3 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[3]/td[1]")).getText();
    	Thread.sleep(4000);
    	String actual_amount4 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[4]/td[1]")).getText();
    	
    	String actual_total = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[5]/td[2]/strong")).getText();
    
    	assertEquals(expected_price1, actual_price1);
    	assertEquals(expected_price2, actual_price2);
    	assertEquals(expected_price3, actual_price3);
    	assertEquals(expected_price4, actual_price4);
    	
    	assertEquals(expected_amount1, actual_amount1);
    	assertEquals(expected_amount2, actual_amount2);
    	assertEquals(expected_amount3, actual_amount3);
    	assertEquals(expected_amount4, actual_amount4);
    	
    	assertEquals(expected_total, actual_total);
    	
    	assertEquals("Name: test", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[1]")).getText());
    	assertEquals("Address: test address", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[2]")).getText());
    	assertEquals("Email: test@test.com", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[3]")).getText());
    	assertEquals("Pay type: Check", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[4]")).getText());
    	
    	assertEquals(expected_name1, driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[2]")).getText());
    	assertEquals(expected_name2, driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[2]/td[2]")).getText());
    	assertEquals(expected_name3, driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[3]/td[2]")).getText());
    	assertEquals(expected_name4, driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[4]/td[2]")).getText());
    }
    
    @Test
    public void purchaseMultipleAmountProductTest() throws InterruptedException
    {
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();	
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();
    	
    	Thread.sleep(4000);
    	String expected_price1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[3]")).getText();
    	
    	Thread.sleep(4000);
    	String expected_amount1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[1]")).getText();
    	
    	Thread.sleep(4000);
    	String expected_total = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[2]/td[2]")).getText();
    	
    	Thread.sleep(4000);
    	String expected_name1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[2]")).getText();
    	
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/form[2]/input")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.id("order_name")).sendKeys("test");
    	driver.findElement(By.id("order_address")).sendKeys("test address");
    	driver.findElement(By.id("order_email")).sendKeys("test@test.com");
    	Select drpType = new Select(driver.findElement(By.id("order_pay_type")));
    	drpType.selectByVisibleText("Check");
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();    	
    	
    	Thread.sleep(4000);
    	String actual_price1 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[3]")).getText();
    	
    	Thread.sleep(10000);
    	String actual_amount1 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[1]")).getText();
    	
    	String actual_total = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[2]/td[2]/strong")).getText();
    
    	assertEquals(expected_price1, actual_price1);    	
    	assertEquals(expected_amount1, actual_amount1);    	
    	assertEquals(expected_total, actual_total);
    	
    	assertEquals("Name: test", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[1]")).getText());
    	assertEquals("Address: test address", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[2]")).getText());
    	assertEquals("Email: test@test.com", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[3]")).getText());
    	assertEquals("Pay type: Check", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[4]")).getText());
    	
    	assertEquals(expected_name1, driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[2]")).getText());
    }
    
    @Test
    public void purchaseAllCategoryProductTest() throws InterruptedException
    {
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();	
    	
    	Thread.sleep(4000);
    	String expected_price1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[3]")).getText();
    	
    	Thread.sleep(4000);
    	String expected_amount1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[1]")).getText();
    	
    	Thread.sleep(4000);
    	String expected_total = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[2]/td[2]")).getText();
    	
    	Thread.sleep(4000);
    	String expected_name1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[2]")).getText();
    	
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/form[2]/input")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.id("order_name")).sendKeys("test");
    	driver.findElement(By.id("order_address")).sendKeys("test address");
    	driver.findElement(By.id("order_email")).sendKeys("test@test.com");
    	Select drpType = new Select(driver.findElement(By.id("order_pay_type")));
    	drpType.selectByVisibleText("Check");
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();    	
    	
    	Thread.sleep(4000);
    	String actual_price1 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[3]")).getText();
    	
    	Thread.sleep(10000);
    	String actual_amount1 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[1]")).getText();
    	
    	String actual_total = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[2]/td[2]/strong")).getText();
    
    	assertEquals(expected_price1, actual_price1);    	
    	assertEquals(expected_amount1, actual_amount1);    	
    	assertEquals(expected_total, actual_total);
    	
    	assertEquals("Name: test", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[1]")).getText());
    	assertEquals("Address: test address", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[2]")).getText());
    	assertEquals("Email: test@test.com", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[3]")).getText());
    	assertEquals("Pay type: Check", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[4]")).getText());
    	
    	assertEquals(expected_name1, driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[2]")).getText());
    	
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();	
    	
    	Thread.sleep(4000);
    	expected_price1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[3]")).getText();
    	
    	Thread.sleep(4000);
    	expected_amount1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[1]")).getText();
    	
    	Thread.sleep(4000);
    	expected_total = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[2]/td[2]")).getText();
    	
    	Thread.sleep(4000);
    	expected_name1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[2]")).getText();
    	
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/form[2]/input")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.id("order_name")).sendKeys("test");
    	driver.findElement(By.id("order_address")).sendKeys("test address");
    	driver.findElement(By.id("order_email")).sendKeys("test@test.com");
    	drpType = new Select(driver.findElement(By.id("order_pay_type")));
    	drpType.selectByVisibleText("Credit card");
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();    	
    	
    	Thread.sleep(4000);
    	actual_price1 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[3]")).getText();
    	
    	Thread.sleep(10000);
    	actual_amount1 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[1]")).getText();
    	
    	actual_total = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[2]/td[2]/strong")).getText();
    
    	assertEquals(expected_price1, actual_price1);    	
    	assertEquals(expected_amount1, actual_amount1);    	
    	assertEquals(expected_total, actual_total);
    	
    	assertEquals("Name: test", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[1]")).getText());
    	assertEquals("Address: test address", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[2]")).getText());
    	assertEquals("Email: test@test.com", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[3]")).getText());
    	assertEquals("Pay type: Credit card", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[4]")).getText());
    	
    	assertEquals(expected_name1, driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[2]")).getText());
    	
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();	
    	
    	Thread.sleep(4000);
    	expected_price1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[3]")).getText();
    	
    	Thread.sleep(4000);
    	expected_amount1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[1]")).getText();
    	
    	Thread.sleep(4000);
    	expected_total = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[2]/td[2]")).getText();
    	
    	Thread.sleep(4000);
    	expected_name1 = driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/table/tbody/tr[1]/td[2]")).getText();
    	
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/form[2]/input")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.id("order_name")).sendKeys("test");
    	driver.findElement(By.id("order_address")).sendKeys("test address");
    	driver.findElement(By.id("order_email")).sendKeys("test@test.com");
    	drpType = new Select(driver.findElement(By.id("order_pay_type")));
    	drpType.selectByVisibleText("Purchase order");
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();    	
    	
    	Thread.sleep(4000);
    	actual_price1 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[3]")).getText();
    	
    	Thread.sleep(10000);
    	actual_amount1 = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[1]")).getText();
    	
    	actual_total = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[2]/td[2]/strong")).getText();
    
    	assertEquals(expected_price1, actual_price1);    	
    	assertEquals(expected_amount1, actual_amount1);    	
    	assertEquals(expected_total, actual_total);
    	
    	assertEquals("Name: test", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[1]")).getText());
    	assertEquals("Address: test address", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[2]")).getText());
    	assertEquals("Email: test@test.com", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[3]")).getText());
    	assertEquals("Pay type: Purchase order", driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/p[4]")).getText());
    	
    	assertEquals(expected_name1, driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/table/tbody/tr[1]/td[2]")).getText());
    }
    
    @Test
    public void purchaseProduct_omitForm_Test() throws InterruptedException
    {	
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();	
    	
    	Thread.sleep(4000);    	
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/form[2]/input")).click();
    
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();    	
    	
    	Thread.sleep(4000);
    	String expected = "Name can't be blank";
    	String actual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li[1]")).getText();
    	assertEquals(expected, actual);
    	Thread.sleep(4000);
    	expected = "Address can't be blank";
    	actual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li[2]")).getText();
    	assertEquals(expected, actual);
    	Thread.sleep(4000);
    	expected = "Email can't be blank";
    	actual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li[3]")).getText();
    	assertEquals(expected, actual);
    	Thread.sleep(4000);
    	expected = "Pay type is not included in the list";
    	actual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li[4]")).getText();
    	assertEquals(expected, actual);
    }
    
    @Test
    public void purchaseProduct_inputEmailWrongForm_Test() throws InterruptedException
    {
    	driver.get(baseUrl);
    	driver.manage().window().maximize();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div[3]/div[2]/form/input[1]")).click();	

    	Thread.sleep(4000);
    	driver.findElement(By.xpath("/html/body/div[4]/div[1]/div/form[2]/input")).click();
    	
    	Thread.sleep(4000);
    	driver.findElement(By.id("order_name")).sendKeys("test");
    	driver.findElement(By.id("order_address")).sendKeys("test address");
    	driver.findElement(By.id("order_email")).sendKeys("test");
    	Select drpType = new Select(driver.findElement(By.id("order_pay_type")));
    	drpType.selectByVisibleText("Check");
    	
    	new WebDriverWait(driver, waitForResposeTime ).ignoring (
    			StaleElementReferenceException.class ).until (
    			ExpectedConditions.elementToBeClickable(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input"))
    			);
    	driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[5]/input")).click();    	
    	
    	String expected = "Email form is wrong";
    	Thread.sleep(4000);
    	String actual = driver.findElement(By.xpath("/html/body/div[4]/div[2]/div/form/div[1]/ul/li")).getText();
    	assertEquals(expected, actual);
    }
    
    @Test
    public void loginLogoutTest() throws InterruptedException{

        login(username, password);
        WebElement adminHeader = driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[1]/a"));
        adminHeader.click();
    	Thread.sleep(4000);
    	String expected = "Logged in user: zelda Edit Delete";
    	String atcual = driver.findElement(By.id("zelda")).getText();
    	assertEquals(expected, atcual);

        logout();
    }
    
    @Test
    public void login_omitForm_Test() throws InterruptedException{

        login("", "");
    	Thread.sleep(4000);
    	String expected = "Invalid user/password combination";
    	String atcual = driver.findElement(By.id("notice")).getText();
    	assertEquals(expected, atcual);
    	Thread.sleep(4000);
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
    }

    @Test
    public void loginFalsePassword() throws InterruptedException {
    	login(username, password + "5");
        WebElement notice = driver.findElement(By.id("notice"));        
    	Thread.sleep(4000);
    	String expected = "Invalid user/password combination";
    	String atcual = notice.getText();
    	assertEquals(expected, atcual);
    }
    
    @Test
    public void deleteLastAccountTest()
    {
    	driver.get(baseUrlAdmin);
    	driver.manage().window().maximize();
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[2]/a")).click();
    	driver.findElement(By.id("name")).sendKeys(username);
    	driver.findElement(By.id("password")).sendKeys(password);
    	driver.findElement(By.xpath("//*[@id=\"login_button\"]/input")).click();
    	
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[1]/a")).click();
    	driver.findElement(By.xpath("//*[@id=\"zelda\"]/a[2]")).click();
    	String expected = "Can't delete last user";
    	String atcual = driver.findElement(By.id("notice")).getText();
    	assertEquals(expected, atcual);

    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[1]/a")).click();
    	expected = "Logged in user: zelda Edit Delete";
    	atcual = driver.findElement(By.id(username)).getText();
    	assertEquals(expected, atcual);
    	driver.findElement(By.xpath("//*[@id=\"menu\"]/ul/li[3]/a")).click();
    }

}
