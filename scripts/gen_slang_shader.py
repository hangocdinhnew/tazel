import sys
import platform
import subprocess
from pathlib import Path

def compile_shader(slang_executable_path, out_path, shader_path, out_name, entryname):
    if platform.system() == "Darwin":
        subprocess.run([slang_executable_path, shader_path,
                                 "-target", "metal",
                                 "-entry", entryname,
                                 "-o", f"{str(out_path)}/{out_name}.msl"], check=True)
        return out_path / f"{out_name}.msl"
    else:
        subprocess.run([slang_executable_path, shader_path,
                                 "-profile", "glsl_450",
                                 "-target", "spirv",
                                 "-entry", entryname,
                                 "-o", f"{str(out_path)}/{out_name}.spv"], check=True)
        return out_path / f"{out_name}.spv"

def write_c_array(out_file, array_name, bin_path):
    data = bin_path.read_bytes()
    out_file.write(f"const unsigned char {array_name}[] = {{\n")
    
    for i in range(0, len(data), 12):
        line = ", ".join(f"0x{b:02x}" for b in data[i:i+12])
        out_file.write(f"    {line},\n")
    
    out_file.write(f"}};\n")
    out_file.write(f"const unsigned int {array_name}_len = {len(data)};\n")

def main():
    if len(sys.argv) < 4:
        print(f"{sys.argv[0]}: slang_executable_path shader_path out_path")
        sys.exit(1)
    
    slang_executable_path = Path(sys.argv[1])
    shader_path = Path(sys.argv[2])
    out_path = Path(sys.argv[3])
    shader_name = shader_path.stem
    shader_name_upper = shader_name.upper()
    shader_ext = shader_path.suffix

    header_vert_path = out_path / f"{shader_name}_vert.h"
    header_frag_path = out_path / f"{shader_name}_frag.h"

    compiled_shader_ext = "None"

    if platform.system() == "Darwin":
        compiled_shader_ext = "MSL"
    else:
        compiled_shader_ext = "SPIR-V"

    if shader_ext == ".slang":
        with header_vert_path.open("w") as f:
            print(f"Compiling Vertex Shader of {shader_name}...")
            
            f.write("/* Auto-generated shader header! DO NOT modify. */\n")
            f.write(f"/* Shader Name: {shader_name}, Shader Type: Vertex. Compiled shader extension: {compiled_shader_ext} */\n")
            f.write(f"#ifndef __{shader_name_upper}_VERT_H\n")
            f.write(f"#define __{shader_name_upper}_VERT_H\n")

            f.write(f"#ifdef __cplusplus\nextern \"C\" {{\n#endif\n")

            vert_output_path = compile_shader(slang_executable_path, out_path, shader_path, f"{shader_name}_vert", "vertMain")
            array_name = f"{shader_name}_vert"
            write_c_array(f, array_name, vert_output_path)

            f.write(f"#ifdef __cplusplus\n}}\n#endif\n")

            f.write(f"#endif /* __{shader_name_upper}_VERT_H */\n")
        with header_frag_path.open("w") as f:
            print(f"Compiling Fragment Shader of {shader_name}...")
            
            f.write("/* Auto-generated shader header! DO NOT modify. */\n")
            f.write(f"/* Shader Name: {shader_name}, Shader Type: Fragment. Compiled shader extension: {compiled_shader_ext} */\n")
            f.write(f"#ifndef __{shader_name_upper}_FRAG_H\n")
            f.write(f"#define __{shader_name_upper}_FRAG_H\n")

            f.write(f"#ifdef __cplusplus\nextern \"C\" {{\n#endif\n")

            frag_output_path = compile_shader(slang_executable_path, out_path, shader_path, f"{shader_name}_frag", "fragMain")
            array_name = f"{shader_name}_frag"
            write_c_array(f, array_name, frag_output_path)

            f.write(f"#ifdef __cplusplus\n}}\n#endif\n")

            f.write(f"#endif /* __{shader_name_upper}_FRAG_H */\n")
    else:
        print(f"Expected file {shader_name}.slang, found {shader_name}.{shader_ext}", file=sys.stderr)
        sys.exit(-1)

if __name__ == "__main__":
    main()
