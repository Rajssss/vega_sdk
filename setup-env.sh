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

#echo "$MDP_TOOLS"
echo "Adding environmet variables to .bashrc"

mdp_sdk_flag=$(grep -o "MDP_SDK" -a ~/.bashrc|wc -l)
if [[ $mdp_sdk_flag == "1" ]]; then
	echo "MDP SDK path already present"
else		
	echo "export MDP_SDK=$MDP_SDK" >> ~/.bashrc	
fi

echo "---------------------------------------------------------------------"
echo "Environment added, Please open new terminal to check the environment"
echo "or you can run command: source ~/.bashrc "
echo "---------------------------------------------------------------------"

