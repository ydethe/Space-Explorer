uniform sampler2D planet_map;
uniform sampler2D planet_map_clouds;

uniform vec2 cloud_position;

const vec4 specular_color = vec4(0.8, 0.7, 0.3, 1.0);

varying float specular_intensity;
varying float diffuse_intensity;

void main(void) {
	vec4 land = texture2D(planet_map, gl_TexCoord[0].xy);
	vec4 clouds = texture2D(planet_map_clouds, gl_TexCoord[0].xy+cloud_position);
	
	vec4 texMix = mix(land, clouds, 0.6);
	gl_FragColor = diffuse_intensity * texMix;
}
