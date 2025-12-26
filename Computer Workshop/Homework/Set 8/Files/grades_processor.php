<?php
// --------------------
// آرایه دانشجویان
// --------------------
$students = [
    [
        'name' => 'آریا قهرمانی',
        'id' => 404171177,
        'major' => 'مهندسی کامپیوتر',
        'grades' => [18, 15, 17, 19]
    ],
    [
        'name' => 'کیوان یکتانسب',
        'id' => 111111111,
        'major' => 'مهندسی برق',
        'grades' => [20, 19, 20, 18]
    ],
    [
        'name' => 'کیتو دوتانسب',
        'id' => 222222222,
        'major' => 'مهندسی کامپیوتر',
        'grades' => [14, 16, 15, 13]
    ],
    [
        'name' => 'کیتری سهتانسب',
        'id' => 333333333,
        'major' => 'مهندسی صنایع',
        'grades' => [12, 14, 13, 15]
    ],
    [
        'name' => 'کیفور چهارتانسب',
        'id' => 4444444444,
        'major' => 'مهندسی مکانیک',
        'grades' => [10, 11, 12, 13]
    ],
    [
        'name' => 'کیفایو پنجتانسب',
        'id' => 5555555555,
        'major' => 'مهندسی شیمی',
        'grades' => [17, 18, 16, 17]
    ],
    [
        'name' => 'کیسیکس ششتانسب',
        'id' => 6666666666,
        'major' => 'مهندسی عمران',
        'grades' => [15, 14, 16, 15]
    ]
];

// --------------------
// توابع
// --------------------
function calculateAverage($grades) {
    return round(array_sum($grades) / count($grades), 1);
}

function getStatus($avg) {
    if ($avg >= 17) return 'عالی';
    if ($avg >= 14) return 'خوب';
    if ($avg >= 12) return 'قابل قبول';
    return 'مردود';
}

function findTopStudent($students) {
    $topStudent = null;
    $maxAvg = 0;

    foreach ($students as $student) {
        $avg = calculateAverage($student['grades']);
        if ($avg > $maxAvg) {
            $maxAvg = $avg;
            $topStudent = $student;
        }
    }
    return $topStudent;
}

function countPassed($students) {
    $count = 0;
    foreach ($students as $student) {
        $passedCourses = 0;
        foreach ($student['grades'] as $grade) {
            if ($grade > 12) $passedCourses++;
        }
        if ($passedCourses >= 3) $count++;
    }
    return $count;
}

// --------------------
// محاسبات کلی
// --------------------
$topStudent = findTopStudent($students);
$passedCount = countPassed($students);

$courseTotals = [0, 0, 0, 0];
foreach ($students as $student) {
    for ($i = 0; $i < 4; $i++) {
        $courseTotals[$i] += $student['grades'][$i];
    }
}
$courseAverages = array_map(fn($t) => round($t / count($students), 1), $courseTotals);

// --------------------
// جستجوی دانشجو با فرم
// --------------------
$searchedStudent = null;
$message = '';

if (isset($_POST['student_id'])) {
    $id = $_POST['student_id'];
    foreach ($students as $student) {
        if ($student['id'] == $id) {
            $searchedStudent = $student;
            break;
        }
    }
    if (!$searchedStudent) {
        $message = 'دانشجویی با این شماره پیدا نشد.';
    }
}
?>

<!DOCTYPE html>
<html lang="fa">
<head>
    <meta charset="UTF-8">
    <title>پردازش نمرات دانشجویان</title>
    <style>
        body { font-family: Tahoma; direction: rtl; }
        table { border-collapse: collapse; width: 100%; margin-bottom: 20px; }
        th, td { border: 1px solid #444; padding: 6px; text-align: center; }
        th { background-color: #eee; }
    </style>
</head>
<body>

<h2>لیست دانشجویان</h2>

<table>
    <tr>
        <th>نام</th>
        <th>شماره دانشجویی</th>
        <th>رشته</th>
        <th>درس ۱</th>
        <th>درس ۲</th>
        <th>درس ۳</th>
        <th>درس ۴</th>
        <th>میانگین</th>
        <th>وضعیت</th>
    </tr>

    <?php foreach ($students as $student): 
        $avg = calculateAverage($student['grades']);
    ?>
    <tr>
        <td><?= $student['name'] ?></td>
        <td><?= $student['id'] ?></td>
        <td><?= $student['major'] ?></td>
        <?php foreach ($student['grades'] as $g): ?>
            <td><?= $g ?></td>
        <?php endforeach; ?>
        <td><?= $avg ?></td>
        <td><?= getStatus($avg) ?></td>
    </tr>
    <?php endforeach; ?>
</table>

<p><strong>دانشجوی با بالاترین میانگین:</strong> <?= $topStudent['name'] ?></p>
<p><strong>تعداد دانشجویانی که حداقل ۳ درس بالای ۱۲ دارند:</strong> <?= $passedCount ?></p>

<p>
<strong>میانگین نمرات دروس:</strong>
درس ۱: <?= $courseAverages[0] ?> |
درس ۲: <?= $courseAverages[1] ?> |
درس ۳: <?= $courseAverages[2] ?> |
درس ۴: <?= $courseAverages[3] ?>
</p>

<hr>

<?php if ($searchedStudent): 
    $avg = calculateAverage($searchedStudent['grades']);
?>
<p>
نام: <?= $searchedStudent['name'] ?><br>
میانگین: <?= $avg ?><br>
وضعیت: <?= getStatus($avg) ?>
</p>
<?php elseif ($message): ?>
<p><?= $message ?></p>
<?php endif; ?>

</body>
</html>
