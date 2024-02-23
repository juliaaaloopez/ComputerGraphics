varying vec2 v_uv;
//we assign to it the uvs of each vertex 

void main()
{	
	// Remember the UV's range [0.0, 1.0]
	v_uv = gl_MultiTexCoord0.xy;
    //

    gl_Position = vec4(gl_Vertex.xyz, 1.0); //we want the glPosition to be in the clip space
    //we have declared the triangles
}
