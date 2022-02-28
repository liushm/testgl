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
		stage("package") {
			steps {
				script {
					bat """
						ZIP -r test_gl_build_%BUILD_DIR%_x64.zip *
					"""
				}
			}
		}
	}
	post{
		success {
			archiveArtifacts artifacts: "test_gl_build_%BUILD_DIR%_x64.zip", fingerprint: true
		}
	}
}