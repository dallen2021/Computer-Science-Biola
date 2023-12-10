<!-- foodorder.php -->
<!DOCTYPE html>
<html lang="en">
<head>
   <title>Christmas Order Form</title>
   <style type="text/css">
      table,th,td{border:  thin solid black;}
      img {
        width: 100%;
        height: auto;
      }
   </style>
</head>
<body>
  <?php
    // Get the customer's name from the form
    $customer = $_POST["customer"];

    // Get the number of appetizers, main dishes, and desserts ordered from the form
    $appetizer_qty = $_POST["aqty"];
    $main_dish_qty = $_POST["mqty"];
    $dessert_qty = $_POST["dqty"];

    // Calculate the total amount for the order
    $total_amount = $appetizer_qty * 45.00 + $main_dish_qty * 130.00 + $dessert_qty * 65.00;

    // Display the customer's name and thank them for the order
    echo "<p>Thank you for your order, $customer!</p>";

    // Display the number of appetizers, main dishes, and desserts ordered
    echo "<p>You ordered $appetizer_qty appetizer(s), $main_dish_qty main dish(es), and $dessert_qty dessert(s).</p>";

    // Display pictures of the items ordered
    echo "<p><img src='https://i.pinimg.com/736x/6a/6f/08/6a6f0889e7fa602f79f9a86a585db11f.jpg' alt='Appetizer' /></p>";
    echo "<p><img src='https://i.pinimg.com/550x/0b/fd/17/0bfd17d30d48bb991a3eebddf89e9b44.jpg' alt='Main Dish' /></p>";
    echo "<p><img src='https://i.pinimg.com/345x/e5/ab/a7/e5aba778c56fa7b246872fae1094f222.jpg' alt='Dessert' /></p>";

    // Display the total amount for the order
    echo "<p>The total amount for your order is: $$total_amount</p>";
  ?>
</body>
</html>