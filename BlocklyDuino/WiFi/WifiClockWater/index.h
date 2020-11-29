String INDEX_PAGE = R"=====(
<!DOCTYPE html>
<html>

<head>
    <meta charset='utf-8'>
    <!--桌面捷徑圖示(要png且去背才可以-->
    <link rel='shortcut icon' href='https://drive.google.com/uc?id=14I56odlAY8v6OX6dLzlGDBc0odLpKQWf' />


    <meta name='viewport' content='width=device-width, initial-scale=1, shrink-to-fit=no'>
    <link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/css/bootstrap.min.css'
        integrity='sha384-TX8t27EcRE3e/ihU7zmQxVncDAy5uIKz4rEkgIXeMed4M0jlfIDPvg6uqKI2xXr2' crossorigin='anonymous'>
    <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.15.1/css/all.css'
        integrity='sha384-vp86vTRFVJgpjF9jiIGPEEqYqlDwgyBgEF109VFjmqGmIY/Y4HV4d3Gp2irVfcrp' crossorigin='anonymous'>
    <script src='https://code.jquery.com/jquery-3.5.1.slim.min.js'
        integrity='sha384-DfXdz2htPH0lsSSs5nCTpuj/zy4C+OGpamoFVy38MVBnE+IbbVYUew+OrCXaRkfj'
        crossorigin='anonymous'></script>
    <script src='https://cdn.jsdelivr.net/npm/bootstrap@4.5.3/dist/js/bootstrap.bundle.min.js'
        integrity='sha384-ho+j7jyWK8fNQe+A12Hb8AhRq26LrZ/JpcUGGOn+Y7RsweNrtN/tE3MoK7ZeZDyx'
        crossorigin='anonymous'></script>
    <title>ANN小花園</title>
</head>

<!--背景-->

<body style='background-image: linear-gradient(-60deg, #16a085 0%, #f4d03f 100%);
            background-repeat: no-repeat;
            background-attachment: fixed;  
            background-size: cover;'>

    <ul class='nav justify-content-center'>
        <!--1/3 首頁 start-->
        <li class='nav-item'>
            <a class='nav-link active' href='#'><i class='fas fa-chevron-circle-left' style='color:white;'></i></a>
        </li>
        <!--1/3 首頁 end-->

        <!--2/3 目前裝置頁面 start-->
        <li class='nav-item' style='margin-left:60px;margin-right: 60px;'>
            <a class='nav-link disabled' href='#' style='color:white;' id='lblDeviceName'>客廳盆栽</a>
        </li>
        <!--2/3 目前裝置頁面 end-->

        <!--3/3 設定頁面 start-->
        <li class='nav-item'>
            <a class='nav-link' href='/set'><i class='fas fa-ellipsis-h' style='color:white;'></i></a>
        </li>
        <!--3/3 設定頁面 end-->
    </ul>

    <div class='d-flex justify-content-center'>
        <img src='https://drive.google.com/uc?id=15RmH0TdpxEy5XGtAeZdZ2CFPAqGW8a9u' id='imgWatering'>
    </div>

    <div style='margin:10px;'></div>

    <div class='d-flex justify-content-center'>
        <div class='btn-group' role='group' aria-label='Basic example'>
            <button id='btnSec_5' type='button' class='btn btn-outline-success'>5秒</button>
            <button id='btnSec_10' type='button' class='btn btn-outline-success'>10秒</button>
            <button id='btnSec_15' type='button' class='btn btn-outline-success'>15秒</button>
            <button id='btnSec_20' type='button' class='btn btn-outline-success'>20秒</button>
            <button id='btnSec_25' type='button' class='btn btn-outline-success'>25秒</button>
        </div>
    </div>

    <div style='margin:10px;'></div>

    <div class='d-flex justify-content-center'>
        <div class='btn-group' role='group' aria-label='Basic example'>
            <button id='btnSec_30' type='button' class='btn btn-outline-success'>30秒</button>
            <button id='btnSec_40' type='button' class='btn btn-outline-success'>40秒</button>
            <button id='btnSec_50' type='button' class='btn btn-outline-success'>50秒</button>
            <button id='btnSec_60' type='button' class='btn btn-outline-success'>1分</button>
            <button id='btnSec_120' type='button' class='btn btn-outline-success'>2分</button>
        </div>
    </div>

    <div style='margin:10px;'></div>

    <div class='d-flex justify-content-center'>

        <div style='margin:5px;'></div>
        <button id='btnStart' type='button' class='btn btn-outline-success'><i class='fas fa-power-off fa-3x'></i>
            On</button>
        <div style='margin:5px;'></div>
        <button id='btnStop' type='button' class='btn btn-outline-danger'><i class='far fa-stop-circle fa-3x'></i>
            Off</button>
    </div>

    <div style='margin:10px;'></div>

    <div role='alert' aria-live='polite' aria-atomic='true' id='toaStart' class='toast' data-delay='1500'>
        <div class='toast-header'>
            <img src='https://drive.google.com/uc?id=1eUOWrk1KdWXGCW-TrjgcQxmrffZOuGt0' class='rounded mr-2' alt='...'>
            <span class='mr-auto'>提醒</span>
            <small>closing 3 seconds</small>
            <button type='button' class='ml-2 mb-1 close' data-dismiss='toast' aria-label='Close'>
                <span aria-hidden='true'>&times;</span>
            </button>
        </div>
        <div class='toast-body' id='toastStart'>
            開始澆花！
        </div>
    </div>

    <div role='alert' aria-live='polite' aria-atomic='true' id='toaStop' class='toast' data-delay='1500'>
        <div class='toast-header'>
            <img src='https://drive.google.com/uc?id=1eUOWrk1KdWXGCW-TrjgcQxmrffZOuGt0' class='rounded mr-2' alt='...'>
            <span class='mr-auto'>提醒</span>
            <small>closing 3 seconds</small>
            <button type='button' class='ml-2 mb-1 close' data-dismiss='toast' aria-label='Close'>
                <span aria-hidden='true'>&times;</span>
            </button>
        </div>
        <div class='toast-body'>
            結束澆花！
        </div>
    </div>


    <script>
        //裝置物件
        var device_id = 'XDs8tTmwwyxUZDRIktW8';
        var device_name = '';

        (function () {
            //澆花圖片動畫
            var picIndex = 0;
            var picCount = 0;
            var pics = new Array();
            var picIntervalId = null;
            pics[0] = 'https://drive.google.com/uc?id=1RoQT731mQR8Tl0cM0ZHSdjH4-3oIaQbE';
            pics[1] = 'https://drive.google.com/uc?id=14I56odlAY8v6OX6dLzlGDBc0odLpKQWf';

            function startPicSlider() {
                picIntervalId = setInterval(function () {
                    picCount++;
                    picIndex = picCount % pics.length;
                    document.getElementById('imgWatering').src = pics[picIndex];
                }, 2000);
            }

            function clearPicSlider() {
                clearInterval(picIntervalId);
                document.getElementById('imgWatering').src = 'https://drive.google.com/uc?id=15RmH0TdpxEy5XGtAeZdZ2CFPAqGW8a9u';
                picIndex = 0;
                picCount = 0;
            }

            //延時秒數下拉清單
            var countDownSecs = 10;//預設澆花秒數
            jQuery(function ($) {
                $(document).on('click', 'button[id^=\'btnSec_\']', function (e) {
                    //秒數群組button的id名稱必須是btnSec_
                    countDownSecs = parseInt(e.target.id.split('_')[1]);
                    console.log(countDownSecs);
                });
            });

            //ESP8266請求與回應
            var httpRequest;
            document.getElementById('btnStart').addEventListener('click', startWaterRequest);
            document.getElementById('btnStop').addEventListener('click', stopWaterRequest);

            function startWaterRequest() {
                httpRequest = new XMLHttpRequest();

                if (!httpRequest) {
                    alert('Giving up :( Cannot create an XMLHTTP instance');
                    return false;
                }
                //httpRequest.timeout = 20000;
                httpRequest.onreadystatechange = alertStart;
                httpRequest.open('GET', '/on?s=' + countDownSecs);
                httpRequest.send();
            }

            function stopWaterRequest() {
                httpRequest = new XMLHttpRequest();

                if (!httpRequest) {
                    alert('Giving up :( Cannot create an XMLHTTP instance');
                    return false;
                }
                httpRequest.onreadystatechange = alertStop;
                httpRequest.open('GET', '/off');
                httpRequest.send();
            }

            function alertStart() {
                if (httpRequest.readyState === XMLHttpRequest.DONE) {
                    if (httpRequest.status === 200) {
                        //alert(httpRequest.responseText);
                        $('#toaStart').toast('show');
                        $('#toastStart').text('開始澆花 ' + countDownSecs + '秒！');
                        startPicSlider();
                        setTimeout(stopWater, countDownSecs * 1000);
                        console.log(httpRequest.responseText);
                    } else {
                        alert('START There was a problem with the request.');
                        //$('#toaStart').toast('show');
                    }
                }
            }

            function alertStop() {
                if (httpRequest.readyState === XMLHttpRequest.DONE) {
                    if (httpRequest.status === 200) {
                        //alert(httpRequest.responseText);
                        //$('#toaStop').toast('show');
                        stopWater();
                        console.log(httpRequest.responseText);
                    } else {
                        alert('STOP There was a problem with the request.');
                        //$('#toaStop').toast('show');                        
                    }
                }
            }

            function stopWater() {
                clearPicSlider();
                $('#toaStop').toast('show');
            }



        })();
    </script>

    <!-- The core Firebase JS SDK is always required and must be listed first -->
    <script src='https://www.gstatic.com/firebasejs/8.1.1/firebase-app.js'></script>
    <script src='https://www.gstatic.com/firebasejs/8.1.1/firebase-firestore.js'></script>

    <script>
        var firebaseConfig = {
            apiKey: '',
            authDomain: 'tp101-263911.firebaseapp.com',
            databaseURL: 'https://tp101-263911.firebaseio.com',
            projectId: 'tp101-263911',
            storageBucket: 'tp101-263911.appspot.com',
            messagingSenderId: '460831034065',
            appId: '1:460831034065:web:52ea0bc43ab89db6e553f0',
            measurementId: 'G-EV0K2XR7WM'
        };
        firebase.initializeApp(firebaseConfig);

        var db = firebase.firestore();
        
        var docRef = db.collection('devices').doc(device_id);
        docRef.get().then(function (doc) {
            if (doc.exists) {
                var device = doc.data();
                //之後要改成class接收db object
                device_name=device.name;
                $('#lblDeviceName').text(device_name);
            } else {
                console.log('No such document!');
            }
        }).catch(function (error) {
            console.log('Error getting document:', error);
        });


    </script>

</body>

</html>

)=====";
