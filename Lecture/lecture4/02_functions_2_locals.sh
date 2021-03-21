#!/bin/bash
function increment1 ()
{
	local temp_return=$1
	let "temp_return = temp_return + 1"
	return $temp_return
}

function increment2 ()
{
	temp_return=$1
	let "temp_return = temp_return + 1"
	return $temp_return
}

echo "## With Local"
increment1 5
temp_grabber=$?
echo $temp_grabber
echo $temp_return

echo "## Without Local"
increment2 5
temp_grabber=$?
echo $temp_grabber
echo $temp_return
