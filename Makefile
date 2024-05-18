##
## EPITECH PROJECT, 2024
## strace
## File description:
## Makefile
##

SRC	=	Src/main.cpp \
		Src/Parsing/Scene.cpp \
		Src/Parsing/Image.cpp \
		Src/Parsing/Camera.cpp \
		Src/Parsing/Subscenes.cpp \
		Src/Parsing/Materials/Materials.cpp \
		Src/Parsing/Materials/Dielectric.cpp \
		Src/Parsing/Materials/ColorBased.cpp \
		Src/Parsing/Materials/GetMaterialTexture.cpp \
		Src/Parsing/Primitives/Primitives.cpp \
		Src/Parsing/Primitives/Sphere.cpp \
		Src/Parsing/Primitives/Quad.cpp \
		Src/Parsing/Primitives/Box.cpp \
		Src/Parsing/Primitives/Cylinder.cpp \
		Src/Parsing/Primitives/Cone.cpp \
		Src/Parsing/Primitives/Obj.cpp \
		Src/Parsing/Primitives/UnlimitedCylinder.cpp \
		Src/Parsing/Primitives/UnlimitedCone.cpp \
		Src/Parsing/Primitives/ConstantMedium.cpp \
		Src/Parsing/Primitives/Triangle.cpp \
		Src/Parsing/Primitives/Torus.cpp \
		Src/Parsing/Matrices/Matrix.cpp \
		Src/Parsing/Matrices/TranslationMatrix.cpp \
		Src/Parsing/Matrices/RotationMatrix.cpp \
		Src/Parsing/Matrices/ScaleMatrix.cpp \
		Src/Parsing/Matrices/ShearMatrix.cpp \
		Src/Math/Math.cpp \
		Src/Math/Vec3.cpp \
		Src/Math/Point3.cpp \
		Src/Math/Aabb.cpp \
		Src/Math/Matrix/Matrix.cpp	\
		Src/Math/Interval.cpp \
		Src/Color.cpp \
		Src/BvhNode.cpp	\
		Src/Camera.cpp	\
		Src/Onb.cpp	\
		Src/Hittable/ConstantMedium.cpp	\
		Src/Hittable/HitRecord.cpp	\
		Src/Hittable/Translate.cpp	\
		Src/Hittable/RotateY.cpp	\
		Src/Hittable/HittableList.cpp	\
		Src/Hittable/Quad.cpp	\
		Src/Hittable/Sphere.cpp	\
		Src/Hittable/Box.cpp \
		Src/Hittable/Cylinder.cpp	\
		Src/Hittable/UnlimitedCylinder.cpp	\
		Src/Hittable/Cone.cpp	\
		Src/Hittable/UnlimitedCone.cpp	\
		Src/Hittable/Torus.cpp	\
		Src/Hittable/Triangle.cpp \
		Src/Hittable/Obj.cpp \
		Src/Material/Material.cpp	\
		Src/Material/Dielectric.cpp	\
		Src/Material/DiffuseLight.cpp	\
		Src/Material/Isotropic.cpp	\
		Src/Material/Lambertian.cpp	\
		Src/Material/Metal.cpp	\
		Src/Pdf/CosinePdf.cpp	\
		Src/Pdf/SpherePdf.cpp	\
		Src/Pdf/HittablePdf.cpp	\
		Src/Pdf/MixturePdf.cpp	\
		Src/Perlin.cpp	\
		Src/Ray.cpp	\
		Src/Texture/CheckerTexture.cpp	\
		Src/Texture/ImageTexture.cpp	\
		Src/Texture/NoiseTexture.cpp	\
		Src/Texture/SolidColor.cpp	\
		Src/SfmlImage.cpp	\
		Src/LibraryHandler.cpp \
		Src/Error/Error.cpp \

OBJ	= $(patsubst Src/%.cpp,build/%.o,$(SRC))
DIRS	=	$(sort $(dir $(OBJ)))

NAME	=	raytracer

CPPFLAGS	=	-g -std=c++20 -I./Includes -O3 -fPIC -fno-gnu-unique -flto -fomit-frame-pointer -msse -msse2 -msse3 -mmmx -m3dnow

SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: build $(NAME)

build:
	mkdir -p $(DIRS)

$(NAME):	$(OBJ)
	make -C plugins/code/MedianFilter
	make -C plugins/code/LowResFilter
	g++ $^ -o $@ $(CPPFLAGS) $(SFML_LIBS) -lconfig++

build/%.o:	Src/%.cpp
	g++ -c $< -o $@ $(CPPFLAGS) $(SFML_LIBS)

clean:
	make clean -C plugins/code/LowResFilter
	make clean -C plugins/code/MedianFilter
	rm -rf build

fclean: clean
	make fclean -C plugins/code/LowResFilter
	make fclean -C plugins/code/MedianFilter
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re build
