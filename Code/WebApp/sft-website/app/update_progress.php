<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_POST['progress'])) {
    $newProgress = intval($_POST['progress']);
    // Cập nhật giá trị progress trong file health.php
    $content = file_get_contents('health.php');
    $content = preg_replace('/\$progress = \d+;/', '$progress = ' . $newProgress . ';', $content);
    file_put_contents('health.php', $content);
    echo "Progress updated successfully";
}
?>