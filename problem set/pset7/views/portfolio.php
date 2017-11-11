<!--<div>
    <iframe allowfullscreen frameborder="0" height="315" src="https://www.youtube.com/embed/oHg5SJYRHA0?autoplay=1&iv_load_policy=3&rel=0" width="420"></iframe>
</div>-->
<table width=70%>
    <tr>
    <th>Symbol</th>
    <th>Name</th>
    <th>Shares</th>
    <th>Price</th>
  </tr>
<?php foreach ($positions as $position): ?>

    <tr>
        <td align="left"><?= $position["symbol"] ?></td>
        <td align="left"><?= $position["name"] ?></td>
        <td align="left"><?= $position["shares"] ?></td>
        <td align="left"><?= $position["price"] ?></td>
    </tr>

<?php endforeach ?>
</table>
