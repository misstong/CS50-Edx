<?php

    // configuration
    require("../includes/config.php"); 

    $rows=CS50::query("SELECT symbol,share FROM portfolios WHERE user_id=?",$_SESSION["id"]);
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["share"],
                "symbol" => $row["symbol"]
            ];
        }
    }
    // render portfolio
    render("portfolio.php", ["positions" => $positions,"title" => "Portfolio"]);

?>
