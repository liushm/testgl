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
		stage("Build") {
			steps {
				script {
					bat """
						mkdir build-%BUILD_ID%
						pushd .
						cd build-%BUILD_ID%

						cmake ..
						cmake --build . --config=release

						popd
					"""
				}
			}
		}
		stage("Package") {
			steps {
				script {
					bat """
						pushd .
						cd build-%BUILD_ID%
						cd release

						ZIP -r test_gl_build_%BUILD_ID%_x64.zip *

						popd
					"""
				}
			}
		}
	}
	post{
		success {
			archiveArtifacts artifacts: "build-%BUILD_ID%/Release/*.zip", fingerprint: true
		}
	}
}