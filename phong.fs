// Global variables from the CPU to send to the GPU
varying mat4 u_model;
varying mat4 u_viewprojection;
varying vec3 u_camera_position;

varying vec3 u_Ka;
varying vec3 u_Ks;
varying vec3 u_Kd;
varying float u_a;

varying vec2 u_lightPosition;
varying vec3 u_diffuseIntensity;
varying vec3 u_specularIntensity;
varying vec3 u_ambientLight;

// Variables passed from the vertex shader
varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;

// pass our texture in uniform type (Image)
uniform sampler2D u_texture_normal;
uniform sampler2D u_texture_color;

void main()
{
	// Set the ouput color per pixel
    vec4 texture_color = texture2D(u_texture_color, v_uv);

    //diffuse reflection
    vec3 L = normalize(vec3(u_lightPosition, 1.0) - v_world_position.xyz); //distance from vertex to light source
    float diffuse = clamp(dot(v_world_normal, L), 0.0, 1.0); //we clamp the dot product between 0 and 1
    vec3 diffuse_reflection = u_Kd * diffuse * u_diffuseIntensity;
    
    //specular reflection --> Ks*(Rm dot V)^a*Im,s
    vec3 R = reflect(-L, v_world_normal);
    vec3 V = normalize(u_camera_position - v_world_position.xyz);
    float specular = pow(clamp(dot(R, V), 0.0, 1.0), u_a);
    vec3 specular_reflection = u_Ks * specular * u_specularIntensity;
    
    //ambient reflection --> Ka*Ia
    vec3 ambient_reflection = u_Ka * u_ambientLight;
    
    // ambient relfection + dist(diffuse relection + specular reflection)
    float dist_ = 1.0/pow(distance(v_world_position, vec3(u_lightPosition, 1.0)), 2.0);
    vec3 frag_color = ambient_reflection + dist_*(specular_reflection + diffuse_reflection);

	gl_FragColor = vec4(frag_color, texture_color[3]);
}
