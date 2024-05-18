# Adding a new Hittable to the raytracer

In this tutorial, we'll walk through the process of adding a new hittable object to the raytracer project. Hittable objects are those that can interact with rays, such as spheres, planes, or custom shapes.

## Prerequisites

Before getting started, make sure you have:

- Basic understanding of C++ programming
- Familiarity with the raytracer project structure

## Step 1: Implement the Hittable interface

The first step is to create a new class that implements the `Hittable` interface. This interface defines several methods that need to be implemented for the hittable object to work correctly.

```cpp
class MyHittable : public Hittable {
public:
    virtual bool hit(const Ray &r, Interval rayT, HitRecord &rec) const override {
        // Implement ray intersection logic here
    }

    virtual Aabb boundingBox() const override {
        // Implement bounding box calculation here
    }

    virtual double pdfValue(const Point3 &origin, const Vec3 &direction) const override {
        // Implement probability density function calculation here
    }

    virtual Vec3 random(const Point3 &origin) const override {
        // Implement random point generation logic here
    }

    virtual std::shared_ptr<Hittable> applyTransformation(const Matrix &matrix) override {
        // Implement transformation application logic here
    }
};
```

## Step 2: Configure the Hittable in the scene

Once the hittable class is implemented, it needs to be configured in the scene. This involves adding the hittable object to the scene configuration file (typically a `.cfg` file).

```cfg
primitives:
{
    myHittable = (
        {
            // Hittable parameters
        }
    );
}
```

## Step 3: Build and test

After implementing and configuring the hittable object, build the project and test the new hittable in the raytracer. Ensure that it behaves as expected and integrates correctly with other components.

## Conclusion

Congratulations! You've successfully added a new hittable object to the raytracer project. Feel free to explore further and add more hittable objects or contribute to other aspects of the project.
