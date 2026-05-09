using UnityEngine;

namespace ParallelCascades.CommonUtilities.Runtime
{
    public class FlyCamera : MonoBehaviour
    {
        public float maxVAngle = 89;
        public float minVAngle = -89;
    
        public float flyRotationSpeed = 1.5f;
        public float flyRotationSharpness = 999999;
        public float flyMoveSharpness = 10;
        public float flyMaxMoveSpeed = 35;
        public float flySprintSpeedBoost = 5;

        private Vector3 _currentMoveVelocity;
        private float _pitchAngle;
        private Vector3 _planarForward = Vector3.forward;
    
        public bool IgnoreInput { get; set; }
    
        private struct CameraInputs
        {
            public Vector3 Move;
            public Vector2 Look;
            public bool Sprint;
        }

        void Update()
        {
            if (Camera.main == null)
            {
                return;
            }
        
            CameraInputs cameraInputs = new CameraInputs
            {
                Move = new Vector3(
                    (Input.GetKey(KeyCode.D) ? 1f : 0f) + (Input.GetKey(KeyCode.A) ? -1f : 0f),
                    (Input.GetKey(KeyCode.E) ? 1f : 0f) + (Input.GetKey(KeyCode.Q) ? -1f : 0f),
                    (Input.GetKey(KeyCode.W) ? 1f : 0f) + (Input.GetKey(KeyCode.S) ? -1f : 0f)),
                Look = new Vector2(
                    Input.GetAxis("Mouse X"),
                    Input.GetAxis("Mouse Y")),
                Sprint = Input.GetKey(KeyCode.LeftShift),
            };
            cameraInputs.Move = cameraInputs.Move *
                                Mathf.Clamp(Vector3.Magnitude(cameraInputs.Move),0,1); // Clamp move inputs magnitude

            if (IgnoreInput)
            { 
                return;
            }
        
            float yawAngleChange = cameraInputs.Look.x * flyRotationSpeed;
            Quaternion yawRotation = Quaternion.Euler(Vector3.up *  yawAngleChange);

            _planarForward = yawRotation * _planarForward;

            _pitchAngle += -cameraInputs.Look.y * flyRotationSpeed;
            _pitchAngle = Mathf.Clamp(_pitchAngle, minVAngle,
                maxVAngle);
            Quaternion pitchRotation = Quaternion.Euler(Vector3.right *  _pitchAngle);

            Quaternion targetRotation =
                Quaternion.LookRotation(_planarForward, Vector3.up) * pitchRotation;
        
            float deltaTime = Time.deltaTime;
        
            var cameraTransform = Camera.main.transform;
        
            cameraTransform.rotation = Quaternion.Slerp(cameraTransform.rotation, targetRotation,
                MathfUtilities.GetSharpnessInterpolant(flyRotationSharpness, deltaTime));

            Vector3 worldMoveInputs = cameraTransform.rotation * cameraInputs.Move;
            float finalMaxSpeed = flyMaxMoveSpeed;
            if (cameraInputs.Sprint)
            {
                finalMaxSpeed *= flySprintSpeedBoost;
            }

            _currentMoveVelocity = Vector3.Lerp(_currentMoveVelocity,
                worldMoveInputs * finalMaxSpeed,
                MathfUtilities.GetSharpnessInterpolant(flyMoveSharpness, deltaTime));
            cameraTransform.position += _currentMoveVelocity * deltaTime;
        }
    }
}