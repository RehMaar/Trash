import java.util.concurrent.TimeUnit;
import org.junit.*;
import static org.junit.Assert.*;

import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.remote.DesiredCapabilities;
import org.openqa.selenium.remote.RemoteWebDriver;

public class TestTransl1 {
        private WebDriver driver;
        private String baseUrl;
        private boolean acceptNextAlert = true;
        private StringBuffer verificationErrors = new StringBuffer();

@Before
public void setUp() throws Exception {
        System.setProperty("webdriver.chrome.driver","C:\\SeleniumGecko\\chromedriver.exe");
        DesiredCapabilities capabilities= DesiredCapabilities.chrome();
        capabilities.setCapability("marionette", true);
        driver = new ChromeDriver();
        baseUrl = "http://www.multitran.ru/";
        driver.manage().timeouts().implicitlyWait(30, TimeUnit.SECONDS);
        }

@Test
public void test2() throws Exception {
        driver.get(baseUrl + "/c/m.exe?a=5&s=DownloadFile");
        driver.findElement(By.cssSelector("img[alt=\"Dicts\"]")).click();
        driver.findElement(By.xpath("//a[contains(text(),'Англо-русский\n  и русско-английский словарь')]")).click();
        driver.findElement(By.id("s")).clear();
        driver.findElement(By.id("s")).sendKeys("cat");
        driver.findElement(By.cssSelector("input[type=\"submit\"]")).click();
        }

@After
public void tearDown() throws Exception {
        driver.quit();
        String verificationErrorString = verificationErrors.toString();
        if (!"".equals(verificationErrorString)) {
        fail(verificationErrorString);
        }
        }

private boolean isElementPresent(By by) {
        try {
        driver.findElement(by);
        return true;
        } catch (NoSuchElementException e) {
        return false;
        }
        }

private boolean isAlertPresent() {
        try {
        driver.switchTo().alert();
        return true;
        } catch (NoAlertPresentException e) {
        return false;
        }
        }

private String closeAlertAndGetItsText() {
        try {
        Alert alert = driver.switchTo().alert();
        String alertText = alert.getText();
        if (acceptNextAlert) {
        alert.accept();
        } else {
        alert.dismiss();
        }
        return alertText;
        } finally {
        acceptNextAlert = true;
        }
        }
        }
