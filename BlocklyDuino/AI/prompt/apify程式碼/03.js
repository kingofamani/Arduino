import { Actor } from 'apify';
import { PuppeteerCrawler } from 'crawlee';

Actor.main(async () => {
    try {
        const crawler = new PuppeteerCrawler({
            launchContext: {
                launchOptions: {
                    headless: true,
                },
            },
            requestHandler: async ({ page, request, log }) => {
                const cookies = [
                    {
            name: 'JSESSIONID',         // 使用 JSESSIONID 作為 session 管理
            value: 'qj6saf5n6tg6vemiw8hwuh65444671b3f89-693f-4893-a24a-a36310bc415d',  // 替換為您實際的 JSESSIONID 值
            domain: 'ecloud.ntpc.edu.tw' // 替換為網站的域名
        },
        // 若其他 Cookies 也必須保留，可以將它們加入到 cookies 陣列中
        {
            name: '_ga',                 // Google Analytics 的 cookie 範例
            value: 'GA1.3.1924290262.1731625627',
            domain: 'ecloud.ntpc.edu.tw'
        },
        {
            name: '_ga_M8YKMN7WKE',
            value: 'GS1.1.1731627539.8.1.1731627677.0.0.0',
            domain: 'ecloud.ntpc.edu.tw'
        },
        {
            name: '_gid',
            value: 'GA1.3.1148425106.1731625627',
            domain: 'ecloud.ntpc.edu.tw'
        },
        {
            name: 'gid',
            value: '111',
            domain: 'ecloud.ntpc.edu.tw'
        },
        {
            name: 'gname',
            value: '%E5%BE%B7%E9%9F%B3%E5%9C%8B%E5%B0%8F',
            domain: 'ecloud.ntpc.edu.tw'
        },
        {
            name: 'groupText',
            value: '%E5%BE%B7%E9%9F%B3%E5%9C%8B%E5%B0%8F',
            domain: 'ecloud.ntpc.edu.tw'
        },
        {
            name: 'lm',
            value: 'zh_TW',
            domain: 'ecloud.ntpc.edu.tw'
        },
        {
            name: 'menu',
            value: '0',
            domain: 'ecloud.ntpc.edu.tw'
        },
        {
            name: 'sso',
            value: 'kSlOETQSkFwwitiT4B2do9sf8qvR6RNP5f1zBcY5N%2bRps%2b1tQ9%2fjaoCchyFQz3sshO52scrbbyi525aVuJb6Q78YRlbkb58unBS1zydpHU%2bx468M1UG3JZA6xXuY2yp97ZMsdT719lKu2%2fXzLS5iXDz30HgpVZmVQGh9f0WBR2wyi27yb9JmwT9US%2fAWHw90LvTm38O3jtcMOJRftoE1ZxWhCEioo%2b%2bS4VLCOGxKv%2bhd%2bYcc3POdSocTPsyPnm3YAeKN5gBQAr%2brwOa5XaH%2byb1cHlIgQJ3CzckpQliStCO5YBeBSsXb0jR10u8SN4u671UauF3%2fkOLIEfXVn33YrFWq%2fQOt7krV2pthC7%2bGracZK6fj1mWhwUDaGjz0I1WsusZsvYeoZd0ac2qDZbUzb7RX3T2b0T94b%2b0ed6%2f2K8IZGxDOufhZHMREgDxYUR%2b5xy1NrzMYZSe9FEdcZ1MBWx6GnmOZEqltTXP3ZQqN1e5T%2faDfGen1PmcJDk3lJEewdFYdMtV7VSP7J5uByPop60tp7UsM2JE1C7vBJfJN2QV00qDja0wxd5DeBVF1T6vkfOhEfwxjT4Fu9YnRBhazdRLOz4OfiC9pyOe34avnsHwX%2f8%2bGnY0q6coLMYrGOsdTUU%2fqdJPbhJ0uxV0JWwAlWEILfSiHoOV9XWwlp%2bLB4WePQrq4Yhsk20kJlHCVNGXkzovuu%2bHMgNLBg3zY%2bDMf0K4w%2fd0EtaIDcPdzpVY%2b583IrrLqO9Y5RmhPZ40YNsF%2f5ifTmHvaMEIevnNVl8tyTtFuUrM3%2fzxeiQuEKjsfh2Z4Smp487%2fxxBw508VrIsOzFrAxGjaAUaFD7Xerpqu5s7ngeK4P2Ew3FQt6KGEZs9vK2Ip9EePVhUmH2eYbChOkUl5syr3r0Ytz%2bSUOwXRvwmK1hsenOj9U%2fW9DJi4JZ%2fHUmoTkV%2fTW9hhEZ4rhIWty5fZEyrjUpoBUe6ab%2fZ04PoJnSrWjJiB%2fW8Ktcqjf75Pc2Qr48bO0OZtpf51f5VGWamwAPQoGLp%2f86oiPHOoliM6Dm0ewQVSO5w17qUeCdpaQnCULx87PyuPFM%2b14t5VveevQiYQ5KqLHxYGNM6GCIjl7zTuWShl%2bb3PifbxxQYN009nQ3IVHjMlq3D57zXig0dJfpX2wpDpWj6W0LyVTH%2f1NMbeuaCZ%2b5D5B%2fOEEM%2b8V60N5YpT3IITlGSUiEK%2b%2bDEpFFXQ3ENlQ89zQ7cedNjSg5QbgyS5rxDnnJXAyuW9nHNV6U5ikvTb5AEGpwBH0KU4cCS6aaI%2bGalkVgT4tdO6CKWGcMC3Q1U6ZgJDeFfBnuCH40noopgdGRaByZe3f6Kstn%2fMrH5KYgLhMIquvEE70FBnc2vfbasc6lp%2bj21FJcREK%2bC%2bTF69o3CXKkM4%2f7e0%2fremkmMjGVs0gcUasKKcR%2bG4T7oWcwL85zo0d1XPx0YACPGUsCC1rdY%2f1lxmbHqAugKhTHoG99GiKtfd8yduYJPx6%2bN0mNwhb8l3wpshqa8n1EOaylma0edrzGrOY9JsbciqzFFsv2UtRT7kz%2fOQCg0kPKLOOuh9Xm3%2bdpLQ%3d',
            domain: 'ecloud.ntpc.edu.tw'
        },
        {
            name: 'mid',
            value: '',
            domain: 'ecloud.ntpc.edu.tw'
        },
        {
            name: 'mname',
            value: '',
            domain: 'ecloud.ntpc.edu.tw'
        }
                ];

                await page.setCookie(...cookies);

                // 導航到受保護的頁面
                await page.goto('https://ecloud.ntpc.edu.tw/ec259801.do');
                
                // 增加等待時間，等待頁面完全加載
                await new Promise(resolve => setTimeout(resolve, 15000)); // 等待 15 秒

                // 抓取整個頁面內容
                const pageData = await page.content();
                
                // 將結果儲存在 Apify 的 Output 頁面
                await Actor.setValue('OUTPUT', pageData);
                log.info('Page content has been saved to the Output page.');
				
            },
        });

        await crawler.run([{ url: 'https://ecloud.ntpc.edu.tw/ec259801.do' }]);
    } catch (error) {
        console.error("An error occurred:", error);
    }
});
