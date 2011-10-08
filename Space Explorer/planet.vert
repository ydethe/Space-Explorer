uniform vec4 light_position;

varying float specular_intensity;
varying float diffuse_intensity;

void main(void) {
	vec4 vertex_position_camera = gl_ModelViewMatrix * gl_Vertex;
	vec3 normal_camera = normalize(gl_NormalMatrix * gl_Normal);
	vec4 light_position_camera = gl_ModelViewMatrix * vec4(10.0 * vec3(light_position), 1.0);

	vec3 light_vector_camera = normalize(vec3(light_position_camera) - vec3(vertex_position_camera));
	diffuse_intensity = max(dot(light_vector_camera, normal_camera), 0.0);

	vec3 reflection_vector_camera = reflect(-light_vector_camera, normal_camera);
	vec3 view_vector_camera = normalize(vec3(-vertex_position_camera));
	specular_intensity = max(dot(reflection_vector_camera, view_vector_camera), 0.0);
	specular_intensity *= pow(diffuse_intensity, 0.1);
	specular_intensity = pow(specular_intensity, 4.0);

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
