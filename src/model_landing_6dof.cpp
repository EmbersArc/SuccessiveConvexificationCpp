#include "model_landing_6dof.h"



void model_landing_6dof::initialize(int K, MatrixXd &X, MatrixXd &U) {

    //initial state
    double m_wet = 2;
    ControlVector r_I_init(4., 4., 0.);
    ControlVector v_I_init(0., -2., -2.);
    Vector4d q_B_I_init(1.0, 0.0, 0.0, 0.0);
    ControlVector w_B_init(0., 0., 0.);
    VectorXd x_init(14);

    //final state
    double m_dry = 1;
    ControlVector r_I_final(0., 0., 0.);
    ControlVector v_I_final(-1e-1, 0., 0.);
    Vector4d q_B_I_final(1.0, 0.0, 0.0, 0.0);
    ControlVector w_B_final(0., 0., 0.);
    VectorXd x_final(14);


    //gravity vector
    ControlVector g_I(-1, 0, 0);

    x_init << m_wet, r_I_init, v_I_init, q_B_I_init, w_B_init;
    x_final << m_dry, r_I_final, v_I_final, q_B_I_final, w_B_final;



    double alpha1, alpha2;
    for(int k=0; k<K; k++) {
        alpha1 = double(K-k)/K;
        alpha2 = double(k)/K;
        X(0, k) = alpha1 * x_init(0) + alpha2 * x_final(0);
        X.col(k).segment(1, 6) = alpha1 * x_init.segment(1, 6) + alpha2 * x_final.segment(1, 6);
        X.col(k).segment(7, 4) << 1., 0., 0., 0.;
        X.col(k).segment(11, 3) = alpha1 * x_init.segment(11, 3) + alpha2 * x_final.segment(11, 3);

        U.col(k) = X(0, k) * -g_I;
    }
}



model_landing_6dof::StateMatrix model_landing_6dof::state_jacobian(const StateVector &x, const ControlVector &u) {
    StateMatrix A;

    double t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23, t24;
    double t25, t26, t27, t28, t29, t30, t31, t32;

    A.setZero();
    t2 = 1.0/(x[0]*x[0]);
    t3 = 1.0/x[0];
    t4 = x[10]*x[10];
    t5 = t4*2.0;
    t6 = x[7]*x[10]*2.0;
    t7 = x[8]*x[9]*2.0;
    t8 = t3*u[2]*x[8]*2.0;
    t9 = t3*u[2]*x[10]*2.0;
    t10 = x[8]*x[8];
    t11 = t10*2.0;
    t12 = x[9]*x[9];
    t13 = t12*2.0;
    t14 = x[7]*x[9]*2.0;
    t15 = x[7]*x[8]*2.0;
    t16 = x[9]*x[10]*2.0;
    t17 = t3*u[0]*x[9]*2.0;
    t18 = t3*u[1]*x[8]*2.0;
    t19 = t3*u[1]*x[7]*2.0;
    t20 = t3*u[1]*x[10]*2.0;
    t21 = t3*u[0]*x[8]*2.0;
    t22 = t3*u[1]*x[9]*2.0;
    t23 = x[13]*(1.0/2.0);
    t24 = x[11]*(1.0/2.0);
    t25 = x[7]*(1.0/2.0);
    t26 = x[12]*(1.0/2.0);
    t27 = x[9]*(1.0/2.0);
    t28 = 1.0/J_B[0];
    t29 = 1.0/J_B[1];
    t30 = J_B[1]*x[12];
    t31 = 1.0/J_B[2];
    t32 = J_B[0]*x[11];
    A(1, 4) = 1.0;
    A(2, 5) = 1.0;
    A(3, 6) = 1.0;
    A(4, 0) = t2*u[2]*(t14-x[8]*x[10]*2.0)-t2*u[1]*(t6+t7)+t2*u[0]*(t5+t13-1.0);
    A(4, 7) = t20-t3*u[2]*x[9]*2.0;
    A(4, 8) = t9+t22;
    A(4, 9) = t18-t3*u[0]*x[9]*4.0-t3*u[2]*x[7]*2.0;
    A(4, 10) = t8+t19-t3*u[0]*x[10]*4.0;
    A(5, 0) = t2*u[1]*(t5+t11-1.0)-t2*u[2]*(t15+t16)+t2*u[0]*(t6-t7);
    A(5, 7) = t8-t3*u[0]*x[10]*2.0;
    A(5, 8) = t17-t3*u[1]*x[8]*4.0+t3*u[2]*x[7]*2.0;
    A(5, 9) = t9+t21;
    A(5, 10) = t3*u[0]*x[7]*-2.0-t3*u[1]*x[10]*4.0+t3*u[2]*x[9]*2.0;
    A(6, 0) = -t2*u[0]*(t14+x[8]*x[10]*2.0)+t2*u[2]*(t11+t13-1.0)+t2*u[1]*(t15-t16);
    A(6, 7) = t17-t18;
    A(6, 8) = -t19+t3*u[0]*x[10]*2.0-t3*u[2]*x[8]*4.0;
    A(6, 9) = t20+t3*u[0]*x[7]*2.0-t3*u[2]*x[9]*4.0;
    A(6, 10) = t21+t22;
    A(7, 8) = x[11]*(-1.0/2.0);
    A(7, 9) = x[12]*(-1.0/2.0);
    A(7, 10) = x[13]*(-1.0/2.0);
    A(7, 11) = x[8]*(-1.0/2.0);
    A(7, 12) = x[9]*(-1.0/2.0);
    A(7, 13) = x[10]*(-1.0/2.0);
    A(8, 7) = t24;
    A(8, 9) = t23;
    A(8, 10) = x[12]*(-1.0/2.0);
    A(8, 11) = t25;
    A(8, 12) = x[10]*(-1.0/2.0);
    A(8, 13) = t27;
    A(9, 7) = t26;
    A(9, 8) = -t23;
    A(9, 10) = t24;
    A(9, 11) = x[10]*(1.0/2.0);
    A(9, 12) = t25;
    A(9, 13) = x[8]*(-1.0/2.0);
    A(10, 7) = t23;
    A(10, 8) = t26;
    A(10, 9) = -t24;
    A(10, 11) = -t27;
    A(10, 12) = x[8]*(1.0/2.0);
    A(10, 13) = t25;
    A(11, 12) = t28*(J_B[1]*x[13]-J_B[2]*x[13]);
    A(11, 13) = t28*(t30-J_B[2]*x[12]);
    A(12, 11) = -t29*(J_B[0]*x[13]-J_B[2]*x[13]);
    A(12, 13) = -t29*(t32-J_B[2]*x[11]);
    A(13, 11) = -t31*(t30-J_B[0]*x[12]);
    A(13, 12) = t31*(t32-J_B[1]*x[11]);

    return A;
}



model_landing_6dof::ControlMatrix model_landing_6dof::control_jacobian(const StateVector &x, const ControlVector &u) {
    ControlMatrix B;
    B.setZero();
    B.row(0) << -alpha_m*u[0]/u.norm(), -(alpha_m*u[1])/u.norm(), -(alpha_m*u[2])/u.norm();
    B.row(4) << -(2*pow(x[9],2) + 2*pow(x[10],2) - 1)/x[0], (2*x[7]*x[10] + 2*x[8]*x[9])/x[0], -(2*x[7]*x[9] - 2*x[8]*x[10])/x[0];
    B.row(5) << -(2*x[7]*x[10] - 2*x[8]*x[9])/x[0], -(2*pow(x[8],2) + 2*pow(x[10],2) - 1)/x[0], (2*x[7]*x[8] + 2*x[9]*x[10])/x[0];
    B.row(6) << (2*x[7]*x[9] + 2*x[8]*x[10])/x[0], -(2*x[7]*x[8] - 2*x[9]*x[10])/x[0], -(2*pow(x[8],2) + 2*pow(x[9],2) - 1)/x[0];
    B.row(11) << 0., -r_T_B[2]/J_B[0], r_T_B[1]/J_B[0];
    B.row(12) << r_T_B[2]/J_B[1], 0., -r_T_B[0]/J_B[1];
    B.row(13) << -r_T_B[1]/J_B[2], r_T_B[0]/J_B[2], 0.;
    return B; 
}



model_landing_6dof::StateVector model_landing_6dof::ode(const StateVector &x, const ControlVector &u) {
    StateVector f;
    f <<
        -alpha_m * u.norm(),
        x[4],
        x[5],
        x[6],
        g_I[0] - (u[0] * (2 * pow(x[9], 2) + 2 * pow(x[10], 2) - 1)) / x[0] + (u[1] * (2 * x[7] * x[10] + 2 * x[8] * x[9])) / x[0] - (u[2] * (2 * x[7] * x[9] - 2 * x[8] * x[10])) / x[0],
        g_I[1] - (u[1] * (2 * pow(x[8], 2) + 2 * pow(x[10], 2) - 1)) / x[0] - (u[0] * (2 * x[7] * x[10] - 2 * x[8] * x[9])) / x[0] + (u[2] * (2 * x[7] * x[8] + 2 * x[9] * x[10])) / x[0],
        g_I[2] - (u[2] * (2 * pow(x[8], 2) + 2 * pow(x[9], 2) - 1)) / x[0] + (u[0] * (2 * x[7] * x[9] + 2 * x[8] * x[10])) / x[0] - (u[1] * (2 * x[7] * x[8] - 2 * x[9] * x[10])) / x[0],
        - (x[8] * x[11]) / 2 - (x[9] * x[12]) / 2 - (x[10] * x[13]) / 2,
        (x[7] * x[11]) / 2 + (x[9] * x[13]) / 2 - (x[10] * x[12]) / 2,
        (x[7] * x[12]) / 2 - (x[8] * x[13]) / 2 + (x[10] * x[11]) / 2,
        (x[7] * x[13]) / 2 + (x[8] * x[12]) / 2 - (x[9] * x[11]) / 2,
        (r_T_B[1] * u[2] - r_T_B[2] * u[1] + J_B[1] * x[12] * x[13] - J_B[2] * x[12] * x[13]) / J_B[0],
        - (r_T_B[0] * u[2] - r_T_B[2] * u[0] + J_B[0] * x[11] * x[13] - J_B[2] * x[11] * x[13]) / J_B[1],
        (r_T_B[0] * u[1] - r_T_B[1] * u[0] + J_B[0] * x[11] * x[12] - J_B[1] * x[11] * x[12]) / J_B[2];
    return f;
}