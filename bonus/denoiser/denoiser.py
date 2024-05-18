import cv2
import sys

def itDenoising(inPath, outPath, modelPath, modelName, scale, it):
    image = cv2.imread(inPath)

    if image is None:
        print("Error: Could not read the input image file.")
        return

    denoiser = cv2.dnn_superres.DnnSuperResImpl_create()
    denoiser.readModel(modelPath)
    denoiser.setModel(modelName, scale)

    for i in range(it):
        denoisedImage = denoiser.upsample(image)

        image = cv2.resize(denoisedImage, (image.shape[1], image.shape[0]))

        cv2.destroyAllWindows()
        del denoisedImage
        print("Completed denoising nb", i + 1)

    cv2.imwrite(outPath, image)
    print(f"Denoised image saved as {outPath}")

def main():
    if len(sys.argv) != 7:
        print("Usage: python3 denoiser.py [input] [output] [model] [modelName] [scale] [it]")
        exit(84)

    inPath = sys.argv[1]
    outPath = sys.argv[2]
    modelPath = sys.argv[3]
    modelName = sys.argv[4]
    scale = int(sys.argv[5])
    it = int(sys.argv[6])

    itDenoising(inPath, outPath, modelPath, modelName, scale, it)

if __name__ == "__main__":
    try:
        main()
    except Exception as e:
        print(e)
        exit(84)

# ? ex: "python3 denoiser.py inputs/in.png outputs/output.png models/EDSR_x4.pb edsr 4 1"
