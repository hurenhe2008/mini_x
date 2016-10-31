#include "mini_random_win.h"

static HCRYPTPROV s_crypt_ctx = NULL;


MINI_NAMESPACE_BEGIN

bool init_rand_ctx()
{
    return CryptAcquireContext(&s_crypt_ctx, nullptr, nullptr, PROV_RSA_FULL, 0)
        ? true : false;
}

int gen_win_random()
{
    if (!s_crypt_ctx) {
        return 0;
    }

    int random = 0;

    CryptGenRandom(s_crypt_ctx, 4, (BYTE *)&random);
    return random;
}

void unit_rand_ctx()
{
    if (s_crypt_ctx) {
        CryptReleaseContext(s_crypt_ctx, 0);
    }
}



RandomWin::RandomWin()
: m_hCryptCtx(NULL)
, m_CurRandom(0)
{
    if (!CryptAcquireContext(&m_hCryptCtx, nullptr, nullptr, PROV_RSA_FULL, 0)) {
        m_hCryptCtx = NULL;
    }
}

RandomWin::~RandomWin()
{
    if (m_hCryptCtx) {
        CryptReleaseContext(m_hCryptCtx, 0);
    }
}

int RandomWin::getRandom()
{
    if (!m_hCryptCtx) {
        return 0;
    }

    m_CurRandom = 0;
    CryptGenRandom(m_hCryptCtx, 4, (BYTE *)&m_CurRandom);
    return m_CurRandom;
}




MINI_NAMESPACE_END