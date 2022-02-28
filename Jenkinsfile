pipeline{
	agent any
	stages{
		stage("Prepare Build"){
			steps{
				script{
					bat """
						@REM ==============================================================================
						@REM PREREQUISITE: JENKINS_VS_DEV_CMD, JENKINS_UE_SRC_UE4, git cmake python in PATH
						@REM ==============================================================================
					"""
				}
			}
		}
		/*stage("package"){
		}*/
	}
	post{
		success {
			archiveArtifacts artifacts: 'glad/src', fingerprint: true, caseSensitive: false
		}
	}
}