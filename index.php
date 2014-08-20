<?php

    $lines = explode("\n", file_get_contents('eg.txt'));

    $pieces = explode(" ", $lines[1]);
    echo '<table>';
    echo '<tr>';
    for ($i=0; $i < 48; $i++) {
        if ($pieces[$i]=="") {
        } else {
            echo '<td>'.$pieces[$i].'</td>';
        }
    }
    echo '</tr>';
    echo '</table>';

?>
