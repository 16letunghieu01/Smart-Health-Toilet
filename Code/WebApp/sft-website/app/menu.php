<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="./sub-sources/css/menu.css">
</head>
<body>
    <div class="menu-box">
        <div class="item menu_item">
            <a class="menu_avatar" style="cursor: pointer;" onclick="myPopup.show()"><i class="fa-solid fa-circle-user"></i></a>
        </div>
        <div class="item menu_item">
            <a href="index.php"><i class="fa-solid fa-house"></i></a>
        </div>
        <div class="item menu_item">
            <a style="cursor: pointer;" onclick="myPopup2.show()" href=""><i class="fa-solid fa-calendar"></i></a>
        </div>
        <div class="line"></div>
        <div class="item"></div>
        <input type="checkbox" name="" id="mode-toggle_btn">
        <label for="mode-toggle_btn">
            <i class="fa-solid fa-moon"></i>
            <i class="fa-solid fa-sun"></i>
            <div class="ball"></div>
        </label>
        <div class="item menu_item">
            <a href=""><i class="fa-solid fa-gear"></i></a>
        </div>
    </div>
</body>
<script>
    const myPopup = new Popup({
        id: "my-popup",
        title: "Thông báo",
    content: `
        Chúng tôi đang phát triển tính năng này, vui lòng quay lại sau.`,
        css: `
        .popup-content {
            font-family: 'Roboto Condensed', sans-serif;
        }
        `
    });
</script>
</html>