const { Builder, By, until } = require('selenium-webdriver');

(async function getCoordinates() {
  let driver;

  try {
    // 啟動內建的 ChromeDriver
    driver = await new Builder().forBrowser('chrome').build();

    // 訪問定位頁面
    console.log('訪問定位頁面...');
    await driver.get('http://127.0.0.1:1880/get-location');

    // 等待 #output 元素出現
    console.log('等待座標出現...');
    await driver.wait(until.elementLocated(By.id('output')), 60000);

    // 獲取 #output 的內容
    const output = await driver.findElement(By.id('output')).getText();
    console.log('座標內容:', output);

    // 提取緯度和經度
    const match = output.match(/緯度: ([0-9.]+), 經度: ([0-9.]+)/);
    if (!match) {
      throw new Error('無法匹配座標，請檢查頁面返回的內容格式');
    }

    const latitude = match[1];
    const longitude = match[2];
    console.log(`成功取得座標: 緯度: ${latitude}, 經度: ${longitude}`);
  } catch (error) {
    console.error('執行出錯:', error.message);
  } finally {
    // 關閉瀏覽器
    if (driver) {
      console.log('關閉瀏覽器...');
      await driver.quit();
    }
  }
})();
