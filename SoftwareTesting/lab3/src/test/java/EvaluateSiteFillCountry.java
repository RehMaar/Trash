
import java.util.regex.Pattern;
import java.util.concurrent.TimeUnit;
import org.junit.*;
import static org.junit.Assert.*;
import static org.hamcrest.CoreMatchers.*;
import org.openqa.selenium.*;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.support.ui.Select;

public class EvaluateSiteFillCountry {
  private WebDriver driver;
  private String baseUrl;
  private boolean acceptNextAlert = true;
  private StringBuffer verificationErrors = new StringBuffer();

  @Before
  public void setUp() throws Exception {
    driver = new ChromeDriver();
    baseUrl = "http://www.multitran.ru/";
    driver.manage().timeouts().implicitlyWait(30, TimeUnit.SECONDS);
  }

  @Test
  public void testEvaluateSiteFillCountry() throws Exception {
    driver.get(baseUrl + "/c/m.exe");
    driver.findElement(By.cssSelector("img[alt=\"Словарь Мультитран\"]")).click();
    driver.findElement(By.cssSelector("img[alt=\"Forum\"]")).click();
    driver.findElement(By.linkText("Оценить сайт")).click();
    driver.findElement(By.name("UserCountry")).clear();
    driver.findElement(By.name("UserCountry")).sendKeys("wertyuio");
    driver.findElement(By.cssSelector("input[type=\"submit\"]")).click();
    assertEquals("Проверьте название своей страны", driver.findElement(By.xpath("//tr[2]/td/table/tbody/tr/td[2]")).getText());
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
