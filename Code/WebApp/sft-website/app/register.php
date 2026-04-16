<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./app/sub-sources/css/register.css">
</head>
<body>
    <div id="register-box" class="register-box">
        <div class="register-header">
            <button type="button" id="login-btn" onclick="login()">ĐĂNG NHẬP</button>
            <button type="button" id="register-btn" onclick="register()">ĐĂNG KÝ</button>
        </div>
        
        <div id="register-line"></div>
        <div class="register-middle">
            <div class="register-social">
                <a href=""><img src="./app/sub-sources/images/facebook-icon.png" alt=""></a>
                <div class="space"></div>
                <a href=""><img src="./app/sub-sources/images/google-icon.png" alt=""></a>
            </div>
            <span>Or</span>
        </div>
        <form id="login-form" class="login-form input-form" method="POST" action="">
            <div class="input-box">
                <input class="input" type="text" name="username" id="username" placeholder="Tên đăng nhập" required>
                <i class="icon fa-regular fa-user"></i>
            </div>
            <div class="input-box">
                <input class="input" type="password" name="password" id="password" placeholder="Mật khẩu" required>
                <i class="icon fa-solid fa-fingerprint"></i>
            </div>  
            <button name="login-submit" type="submit" id="register-btn">ĐĂNG NHẬP</button>
        </form>


        <?php
            include("./sources/php/config.php");
            if(isset($_POST['submit'])) {
                $username = $_POST['username'];
                $password = $_POST['password'];
                $verify_query = mysqli_query($con, "SELECT * FROM users WHERE username = '$username' AND password = '$password'");
                
                if (mysqli_num_rows($verify_query) > 0) {
                    echo '<div style="text-align: center; margin-top: 100px; border: 2px solid #FF4545; border-radius: 10px; padding: 15px 0; background: #9eded; color: red; font-weight: bold; font-family: Roboto Condensed, sans-serif; font-size: 18px;" class="message">
                        <p>Tên đăng nhập đã tồn tại, hãy thử một tên đăng nhập khác!</p>
                    </div> <br>';
                    echo '<a href ="javascript:history.back()"><button style="background: #FF4545; color: #fff; font-weight: bold; position: relative; left: 50%; transform: translateX(-50%); cursor: pointer; font-family: Roboto Condensed, sans-serif; font-size: 18px; border: 2px solid #FF4545; border-radius: 10px; padding: 10px 20px; margin-top: 10px;" class="back-btn">Quay về</button></a>';
                } else {
                    mysqli_query($con, "INSERT INTO users (username, password) VALUES ('$username', '$password')") or die("Đã xảy ra lỗi");
                    echo '<div style="text-align: center; margin-top: 100px; border: 2px solid #59b65a; border-radius: 10px; padding: 15px 0; background: #9eded; color: #59b65a; font-weight: bold; font-family: Roboto Condensed, sans-serif; font-size: 18px;" class="message">

                        <p>Đăng ký thành công!</p>
                    </div> <br>';
                    echo '<a href ="javascript:history.back()"><button style="background: #59b65a; color: #fff; font-weight: bold; font-family: Roboto Condensed, sans-serif; font-size: 18px; border: 2px solid #59b65a; border-radius: 10px; padding: 10px 20px; margin-top: 10px;" class="back-btn">Đăng nhập ngay</button></a>';
                }
            } else {
        ?>
        <form id="register-form" class="register-form input-form" method="POST" action="">
            <div class="input-box">
                <input class="input" type="text" name="username" id="username" placeholder="Tên đăng nhập">
                <i class="icon fa-regular fa-user"></i>
            </div>
            <div class="input-box">
                <input class="input" type="password" name="password" id="password" placeholder="Mật khẩu">
                <i class="icon fa-solid fa-fingerprint"></i>
            </div>
            <div class="input-box">
                <input class="input" type="password" name="password" id="password" placeholder="Nhập lại mật khẩu">
                <i class="icon fa-solid fa-fingerprint"></i>
            </div>
            <button name="submit" type="submit" id="register-btn">ĐĂNG KÝ</button>
        </form>
        <?php
            }
        ?>
    </div>
</body>
<script>
    var line = document.getElementById("register-line");
    var loginForm = document.getElementById("login-form");
    var registerForm = document.getElementById("register-form");
    
    function login() {
        line.style.left = "30px";
        loginForm.style.left = "50%";
        loginForm.style.transform = "translateX(-50%)";
        registerForm.style.transform = "translateX(170%)";
    }
    function register() {
        line.style.left = "250px";
        loginForm.style.transform = "translateX(-170%)";
        registerForm.style.transform = "translateX(50%)";
        
    }
    
</script>
</html>