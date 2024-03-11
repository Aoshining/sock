import numpy as np
from numpy import int64


def bilinear_interp_vectorized(a: np.ndarray, b: np.ndarray) -> np.ndarray:
    """
    This is the vectorized implementation of bilinear interpolation.
    - a is a ND array with shape [N, H1, W1, C], dtype = int64
    - b is a ND array with shape [N, H2, W2, 2], dtype = float64
    - return a ND array with shape [N, H2, W2, C], dtype = int64
    """
    # get axis size from ndarray shape
    N, H1, W1, C = a.shape
    N1, H2, W2, _ = b.shape
    assert N == N1

    # TODO: Implement vectorized bilinear interpolation
    res = np.empty((N, H2, W2, C), dtype=int64)
    x,y=b[...,0],b[...,1]
    x_idx=np.floor(x).astype(int)
    y_idx=np.floor(y).astype(int)
    _x,_y=x-x_idx,y-y_idx
    w1=(1-_x)*(1-_y)
    w2=_x*(1-_y)
    w3=(1-_x)*_y
    w4=_x*_y
    res=a[np.arange(N)[:,None,None],x_idx,y_idx]*w1[...,None]+\
        a[np.arange(N)[:,None,None],x_idx+1,y_idx]*w2[...,None]+\
        a[np.arange(N)[:,None,None],x_idx,y_idx+1]*w3[...,None]+\
        a[np.arange(N)[:,None,None],x_idx+1,y_idx+1]*w4[...,None]
    return res.astype(int)
