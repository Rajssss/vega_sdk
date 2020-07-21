 ######################################################################
 #
 #				File Name: main.c
 #
 ######################################################################
 #
 # Project Name		: MDP - Microprocessor Development Project
 #
 # Project Code		: HD083D
 #
 # Created			: 07-Nov-2019
 #
 # Purpose			: Environment script
 #
 # Description		: Environment script
 #
 # Author(s)		: Premjith A V
 #
 # Version No		: 1.0.0
 #
 # Revisions		:
 #
 # Remarks			: 
 #
 # Copyright		: 2019, C-DAC, Trivandrum
 ######################################################################
#/bin/bash

MDP_SDK=`pwd`

CONFIG_PATH=~/.config/mdp-tools
mkdir -p $CONFIG_PATH

set_property(){
filename=$CONFIG_PATH/settings.mk

if ! grep -R "^[#]*\s*${1}=.*" $filename &> /dev/null; then
  #echo "APPENDING because '${1}' not found"
  echo "$1=$2" >> $filename 
else
  #echo "SETTING because '${1}' found already"
  sed -i "s|^[#]*\s*${1}=.*|$1=$2|" $filename
fi
}

get_property()
{
 filename=$CONFIG_PATH/settings.mk
 sed -rn "s/^${1}=([^\n]+)$/\1/p" $filename
}


echo "Setting up MDP SDK environmet"

set_property "MDP_SDK" "$MDP_SDK"

echo "MDP SDK Environment added"

mdp_tool_flag=$(get_property "MDP_TOOLS")

if [ -z "$mdp_tool_flag" ]
then
      echo "WARNING: Please install mdp-tools, and setup environment!"
fi




