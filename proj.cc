#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::vec3;
using glm::vec4;

int main()
{
	glm::mat4 v = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 p = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 0.1f);

	// GLM的矩阵是列主序的，（按列向量顺序存放）
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			printf("%8.4f ", p[i][j]);
		}
		printf("\n");
	}
	printf("\n");

#if 0
	p = glm::translate(p, glm::vec3(10, 10, 10));
	for (int j = 0; j < 4; j++)
	{
		for (int i = 0; i < 4; i++)
		{
			printf("%f ", p[i][j]);
		}
		printf("\n");
	}
#endif

	glm::vec4 pos = glm::vec4(0.0f, 0.0f, -0.0999f, 1.0f);

	glm::vec4 toz = p * pos;

	// toz.z/toz.w在[-1, 1]之外的就会被裁剪掉，对应于eye空间的[-0.1, -100.0]
	printf("%f %f %f %f, %f\n", toz.x, toz.y, toz.z, toz.w, toz.z/toz.w);

	system("pause");
	return 0;
}