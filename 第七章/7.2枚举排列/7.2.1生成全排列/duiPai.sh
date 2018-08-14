count=1
while true
do
    expr $RANDOM % 6 + 1 > fileIn
    ./test < fileIn > fileOut.test
    ./solution < fileIn > fileOut.solu
    echo "对拍${count}次"
    ((count++))
    diff fileOut.test fileOut.solu
    if [[ $? != 0 || count -ge 100 ]]
    then
	break
    fi
done
