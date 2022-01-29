#!/bin/bash

echo "<TABLE>" > $2

# 1. Add <TR><TD> at the beginning of each line
# 2. Change all commas to </TD><TD>
# 3. Add </TD></TR> at the end of each line
sed -e 's/^/<TR><TD>/' -e 's~,~</TD><TD>~g' -e 's~$~</TD></TR>~' $1 >> $2

echo '</TABLE>' >> $2
