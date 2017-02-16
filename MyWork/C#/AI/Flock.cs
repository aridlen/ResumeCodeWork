///////////////////////////////////////////
//                                       //
//       THIS IS THE WORK OF:            //
//     Programmer: Aaron Ridlen          //
//     Instructor: Johnathan Burnsides   //
//      Date:  10/24/2016                //
//                                       //
///////////////////////////////////////////
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using FullSailAFI.SteeringBehaviors.Core;

namespace FullSailAFI.SteeringBehaviors.StudentAI
{
    public class Flock
    {
        public float AlignmentStrength { get; set; }
        public float CohesionStrength { get; set; }
        public float SeparationStrength { get; set; }
        public List<MovingObject> Boids { get; protected set; }
        public Vector3 AveragePosition { get; set; }
        protected Vector3 AverageForward { get; set; }
        public float FlockRadius { get; set; }

        #region Constructors
        public Flock()
        {
        }
        #endregion

        #region helper methods

        private void CalculateAverages()
        {
            Vector3 avePos= Vector3.Zero;
            Vector3 aveFor = Vector3.Zero;
            for (int i=0;i<Boids.Count;++i)
            {
                avePos += Boids[i].Position;
                aveFor += Boids[i].Velocity;
            }
            aveFor /= Boids.Count;
            avePos /= Boids.Count;
            AveragePosition = avePos;
            AverageForward = aveFor;
            return;
        }

        private Vector3 CalculateAlignmentAcceleration(MovingObject boid)
        {
            Vector3 vec = AverageForward / boid.MaxSpeed;
            if (vec.Length > 1)
                vec.Normalize();
            return vec*AlignmentStrength;
        }

        private Vector3 CalculateCohesionAcceleration(MovingObject boid)
        {
            Vector3 temp = AveragePosition - boid.Position;
            float dis = temp.Length;
            temp.Normalize();
            if(dis<FlockRadius)
            {
                temp *= dis / FlockRadius;
            }
            
            return temp*CohesionStrength;
        }

        private Vector3 CalculateSeparationAcceleration(MovingObject boid)
        {
            Vector3 sum=Vector3.Empty;
            for(int i=0;i<Boids.Count;++i)
            {
                Vector3 vec = boid.Position - Boids[i].Position;
                float dis = vec.Length;
                float safeDis = boid.SafeRadius + Boids[i].SafeRadius;
                if(dis<safeDis)
                {
                    vec.Normalize();
                    vec *= (safeDis - dis) / safeDis;
                    sum += vec;
                }
            }
            if (sum.Length > 1.0f)
                sum.Normalize();
            return sum*SeparationStrength;
        }

        #endregion

        #region LabFunctions

        public virtual void Update(float deltaTime)
        {
            CalculateAverages();
            Vector3 accel;
            float accelMulti = 0;
            for (int i = 0; i < Boids.Count; ++i)
            {
                accel = CalculateAlignmentAcceleration(Boids[i]);
                accel += CalculateCohesionAcceleration(Boids[i]);
                accel += CalculateSeparationAcceleration(Boids[i]);
                accelMulti = Boids[i].MaxSpeed;

                accel *= accelMulti * deltaTime;
                Boids[i].Velocity += accel;

                if(Boids[i].Velocity.Length> Boids[i].MaxSpeed)
                {
                    Boids[i].Velocity.Normalize();
                    Boids[i].Velocity *= Boids[i].MaxSpeed;
                }

                Boids[i].Update(deltaTime);
            }
                
        }
        #endregion
    }
}
