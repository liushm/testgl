pipeline{
	agent any
	stages{
		stage("Prepare Build"){
			//MY_VERSION = bat(script:'python --version', returnStdout: true)

			steps{
				script{
					println "hello, fuck!"
					println "bye, fuck!"

					browsers = ['chrome','firefox']
                    for (int i = 0;i < browers.size();++i) {
                        println "Testing the ${browsers[i]} browser"
                    }

					bat """
						@REM ==============================================================================
						@REM PREREQUISITE: JENKINS_VS_DEV_CMD, JENKINS_UE_SRC_UE4, git cmake python in PATH
						@REM ==============================================================================

						echo %VERSION%
						echo %MY_VERSION%
						@REM echo ${MY_VERSION}
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