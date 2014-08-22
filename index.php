<?php

    $lines = explode("\n", file_get_contents('glassesonly.txt'));

    echo '<table>';
    for ($i=0; $i < 50; $i++) {
        $pieces = explode(",", $lines[i]);
        echo '<tr>';
        for ($i=0; $i < 48; $i++) {
                echo '<td>'.$pieces[$i].'</td>';
        }
        echo '</tr>';
    }
    echo '</table>';

?>
