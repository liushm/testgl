pipeline{
	agent any
	environment {
		MY_VERSION = bat(script:'python --version', returnStdout: true).strip()
	}
	stages{
		stage("Prepare Build"){
			steps{
				script{
					println "hello, fuck!"
					println "bye, fuck!"

					def abcd = bat(script:'python --version', returnStdout: true).trim()
					println "${abcd}"

					bat """
						@REM ==============================================================================
						@REM PREREQUISITE: JENKINS_VS_DEV_CMD, JENKINS_UE_SRC_UE4, git cmake python in PATH
						@REM ==============================================================================

						echo %VERSION%
						echo %MY_VERSION%
						python test.py 1 2 3 4 ${MY_VERSION}
						echo %BUILD_ID%
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

						ZIP -r test_gl_build_${env:MY_VERSION}_x64.zip *

						popd
					"""
				}
			}
		}
	}
	post{
		success {
			archiveArtifacts artifacts: "build-${MY_VERSION}/Release/*.zip", fingerprint: true
		}
	}
}