<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Greeneration</title>
    <link rel="icon" type="image/x-icon" href="./sources/images/icon/1favicon.ico">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Outfit:wght@100..900&display=swap" rel="stylesheet">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Outfit:wght@100..900&family=Roboto+Condensed:ital,wght@0,100..900;1,100..900&display=swap" rel="stylesheet">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/6.6.0/css/all.min.css" integrity="sha512-Kc323vGBEqzTmouAECnVceyQqyqdsSiqLQISBL29aUW4U/M7pSPA/gEUZQqv1cwx4OnYxTxve5UMg5GT6L4JJg==" crossorigin="anonymous" referrerpolicy="no-referrer" />
    <script src="https://cdnjs.cloudflare.com/ajax/libs/three.js/0.168.0/three.module.js" integrity="sha512-cV5o5uoKbUWe+4GaJ4Eu/oaZ4IJKh2OhShH7Gwub0OQ6oPgxQxXL++Ih6AJJk70O/JCBhf9nxAm+Hhsx1ddk1g==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
    <!-- main css start -->
    <link rel="stylesheet" href="./app/sub-sources/css/header.css">
    <link rel="stylesheet" href="./app/sub-sources/css/menu.css">
    <link rel="stylesheet" href="./app/sub-sources/css/register.css">
    <link rel="stylesheet" href="./app/sub-sources/css/device.css">
    <link rel="stylesheet" href="./app/sub-sources/css/health.css">
    <link rel="stylesheet" href="./app/sub-sources/css/toggle.css">
    <link rel="stylesheet" href="./sources/css/index.css">
    <!-- main css end -->
    <script src="https://cdn.jsdelivr.net/npm/@simondmc/popup-js@1.4.3/popup.min.js"></script>
</head>
<body>
    <div id="main_content">
        <div id="main_box" class="main_box">
            <header>
                <?php 
                    include("./app/header.php")
                ?>
            </header>
            <div class="content">
                <div class="menu">
                    <?php 
                        include("./app/menu.php")
                    ?>
                </div>
                <div class="register">
                    <?php 
                        include("./app/register.php")
                    ?>
                </div>
                <div class="device">
                    <?php 
                        include("./app/device.php")
                    ?>
                </div>
                <div class="health">
                    <?php 
                        include("./app/health.php");
                    ?>
                </div>
            </div>
            <footer><span>2024@wearegearbot</span></footer>
        </div>
        
    </div>
    <script src="./app/sub-sources/js/togglemode.js"></script>
</body>

</html>